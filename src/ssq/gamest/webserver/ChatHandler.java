package ssq.gamest.webserver;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

import org.apache.http.HttpEntity;
import org.apache.http.HttpEntityEnclosingRequest;
import org.apache.http.HttpException;
import org.apache.http.HttpRequest;
import org.apache.http.HttpResponse;
import org.apache.http.entity.StringEntity;
import org.apache.http.protocol.HttpContext;
import org.apache.http.protocol.HttpRequestHandler;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;

import ssq.gamest.port.android.App;
import ssq.utils.LogUtilities;
import android.content.Context;
import android.util.SparseArray;

public class ChatHandler implements HttpRequestHandler {
	private final ReentrantLock lock = new ReentrantLock();
	private final Condition newMessageReceived = lock.newCondition();

	private int counter = -1;
	private final int MAX_MESSAGES_SAVED = 30;
	SparseArray<String> Lastmessages = new SparseArray<String>();
	Map<String, String> newContent = new HashMap<String, String>();

	public ChatHandler(Context context){
	}

	@Override
	public void handle(HttpRequest request, HttpResponse response, HttpContext httpContext) throws HttpException, IOException {
		String bodyResponse = new String();
		LogUtilities.logString("CH:UpdateHandling: " + request.getRequestLine().getMethod());

		if (request instanceof HttpEntityEnclosingRequest) { //test if request is a POST
			HttpEntity entity = ((HttpEntityEnclosingRequest) request).getEntity();
			String body = EntityUtils.toString(entity); //here you have the POST body
			try {
				// Parsing JSon request
				JSONObject mjsReceived = new JSONObject(body);
				String command = mjsReceived.getString("command");
				if(command != null ){
					LogUtilities.logString("CH: command: " + command);
					if(command.equals("newMessage")){
						registerNewMessage(mjsReceived.getString("message"),mjsReceived.getString("author"));			    		
					}else if(command.equals("waitingUpdate")){
						bodyResponse = getUpdate(mjsReceived.getInt("lastMsgId"));
					}
				}
				response.setHeader("Content-Type", "text/plain; charset=UTF-8");
				response.setEntity(new StringEntity(bodyResponse));
				LogUtilities.logString("Respond Post: " + bodyResponse);

			} catch (JSONException e) {
				e.printStackTrace();
			} 
		}


	}
	private Boolean registerNewMessage(String message, String author){

		lock.lock();
		if(message != null){
			LogUtilities.logString("New content Post: " + message);
			if(counter == Integer.MAX_VALUE)
				counter = 1;
			else
				counter++;

			if(counter - MAX_MESSAGES_SAVED > 0)
				Lastmessages.delete(counter - MAX_MESSAGES_SAVED);
			if(author.equals(""))
				author = "Unknown";
			Lastmessages.put(counter, author + ": " + message);

			// Release all handler waiting a message
			newMessageReceived.signalAll();
			lock.unlock();
			return true;
		}else{
			LogUtilities.logWarningString("Null message");
			lock.unlock();
			return false;
		}


	}

	private String getUpdate(int lastMessageNumberReceived){

		String messageToSend = new String();
		int currentCounter = counter;

		if(lastMessageNumberReceived > currentCounter){
			lastMessageNumberReceived = -1;
		}

		if(currentCounter == lastMessageNumberReceived){
			// Waiting for new messages
			lock.lock();
			try {
				while(counter == currentCounter){
					newMessageReceived.await();
				}
				currentCounter = counter;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} finally {
				lock.unlock();
			}
		}
		LogUtilities.logString("currentCounter: " + currentCounter + " :: lastMessageNumberReceived: " +lastMessageNumberReceived);
		if(currentCounter - lastMessageNumberReceived > MAX_MESSAGES_SAVED)
			lastMessageNumberReceived = currentCounter - MAX_MESSAGES_SAVED;
		for (int i=lastMessageNumberReceived+1;i <= currentCounter; i++)
			messageToSend += Lastmessages.get(i, "Plop System ^^") + "\n";

		LogUtilities.logString("Stop Awaiting ...");
		newContent.put("updateContent",messageToSend);
		newContent.put("msgId","" + currentCounter);
		JSONObject mjsToSend = new JSONObject(newContent);

		return mjsToSend.toString();
	}

}
