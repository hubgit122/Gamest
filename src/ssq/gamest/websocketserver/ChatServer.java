package ssq.gamest.websocketserver;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.security.KeyStore;
import java.util.Collection;

import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManagerFactory;

import org.java_websocket.WebSocket;
import org.java_websocket.WebSocketImpl;
import org.java_websocket.framing.Framedata;
import org.java_websocket.handshake.ClientHandshake;
import org.java_websocket.server.DefaultSSLWebSocketServerFactory;
import org.java_websocket.server.WebSocketServer;

/**
 * A simple WebSocketServer implementation. Keeps track of a "chatroom".
 */
public class ChatServer extends WebSocketServer
{
	
	public ChatServer(int port) throws UnknownHostException
	{
		super(new InetSocketAddress(port));
	}
	
	public ChatServer(InetSocketAddress address)
	{
		super(address);
	}
	
	@Override
	public void onOpen(WebSocket conn, ClientHandshake handshake)
	{
		this.sendToAll("new connection: " + handshake.getResourceDescriptor());
		System.out.println(conn.getRemoteSocketAddress().getAddress().getHostAddress() + " entered the room!");
	}
	
	@Override
	public void onClose(WebSocket conn, int code, String reason, boolean remote)
	{
		this.sendToAll(conn + " has left the room!");
		System.out.println(conn + " has left the room!");
	}
	
	@Override
	public void onMessage(WebSocket conn, String message)
	{
		this.sendToAll(message);
		System.out.println(conn + ": " + message);
	}
	
	@Override
	public void onFragment(WebSocket conn, Framedata fragment)
	{
		System.out.println("received fragment: " + fragment);
	}
	
	public static void main(String[] args) throws Exception
	{
		WebSocketImpl.DEBUG = true;
		int port = 8887; // 843 flash policy port
		try
		{
			port = Integer.parseInt(args[0]);
		}
		catch (Exception ex)
		{
		}
		ChatServer s = new ChatServer(port);
		
		try
		{
			// load up the key store
			String STORETYPE = "JKS";
			String KEYSTORE = "E:\\Projects\\html\\java_websocket\\keys\\server.jks";
			String STOREPASSWORD = "830576";
			
			SSLContext ctx = SSLContext.getInstance("SSL");
			
			KeyManagerFactory kmf = KeyManagerFactory.getInstance("SunX509");
			TrustManagerFactory tmf = TrustManagerFactory.getInstance("SunX509");
			
			KeyStore ks = KeyStore.getInstance(STORETYPE);
			KeyStore tks = KeyStore.getInstance(STORETYPE);
			
			ks.load(new FileInputStream("E:\\Projects\\html\\java_websocket\\keys\\kserver.keystore"), STOREPASSWORD.toCharArray());
			tks.load(new FileInputStream("E:\\Projects\\html\\java_websocket\\keys\\tserver.keystore"), STOREPASSWORD.toCharArray());
			
			kmf.init(ks, STOREPASSWORD.toCharArray());
			tmf.init(tks);
			
			ctx.init(kmf.getKeyManagers(), tmf.getTrustManagers(), null);
			
			DefaultSSLWebSocketServerFactory sslf = new DefaultSSLWebSocketServerFactory(ctx);
			s.setWebSocketFactory(sslf);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		
		s.start();
		System.out.println("ChatServer started on port: " + s.getPort());
		
		BufferedReader sysin = new BufferedReader(new InputStreamReader(System.in));
		while (true)
		{
			String in = sysin.readLine();
			s.sendToAll(in);
			if (in.equals("exit"))
			{
				s.stop();
				break;
			}
			else if (in.equals("restart"))
			{
				s.stop();
				s.start();
				break;
			}
		}
	}
	
	@Override
	public void onError(WebSocket conn, Exception ex)
	{
		ex.printStackTrace();
		if (conn != null)
		{
			// some errors like port binding failed may not be assignable to a specific websocket
		}
	}
	
	/**
	 * Sends <var>text</var> to all currently connected WebSocket clients.
	 * 
	 * @param text
	 *            The String to send across the network.
	 * @throws InterruptedException
	 *             When socket related I/O errors occur.
	 */
	public void sendToAll(String text)
	{
		Collection<WebSocket> con = connections();
		synchronized (con)
		{
			for (WebSocket c : con)
			{
				c.send(text);
			}
		}
	}
}
