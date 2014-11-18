#encoding="utf-8"
import os
import json
import copy
import re
import shutil

projectDir = os.getcwd()
config =  {
    "defined": {},
    "deleteComment": {
        "c": 0,
        "classpath": 0,
        "cpp": 0,
        "h": 0,
        "java": 0,
        "project": 0,
        "xml": 0
    },
    "exclude": {
        "All": [
            "jni/core/jniCore"
        ],
        "Android": [
            "libs/sqlite-jdbc.*"
        ],
        "Java": [
            "libs/sqldroid.*"
        ]
    },
    "extract": {
        "All": [
            "src/.*",
            "libs/.*",
            "assets/.*",
            "jni/.*",
            "\\.classpath",
            "\\.project"
        ],
        "Android": [
            "res/.*",
            "gen/.*",
            "androidmanifest\\.xml",
            "proguard\\.cfg",
            "project\\.properties"
        ],
        "Java": []
    },
    "lineCommentBeginString": {
        "classpath": "<!--",
        "project": "<!--",
        "java": "//",
        "xml": "<!--",
        "c" : "//",
        "cpp": "//",
        "h": "//",
    },
    "platform": "Android",
    "process": [
        r"src/.*\.java",
        r"\.classpath",
        r"\.project"
    ]
}

platform = ""
process=[] #������ʽ��ʾ�����·���б�, ��ʾ��Ҫ�������define��platform��Ԥ����
predefined= {} #define���ļ�-ֵ, ��Դ��config.repackage��process�б��е��ļ�. ÿ���ļ��������, �ָ���config��״̬
defined = {}
extract=[] #��ǰƽ̨��Ҫ����ȡ���ļ������·����������ʽ
exclude = [] #��ǰƽ̨��Ҫ���ų����ļ������·����������ʽ, ʵ����ȡ����{extract}-{exclude}
handled = False
word = re.compile("[a-zA-Z_][a-zA-Z_0-9]*")
nonspace = re.compile(r"[^\s]+")
defWord = re.compile(r"`[a-zA-Z_][a-zA-Z_0-9]*`")

#process�����ļ�Ԥ��������ע�͸�ʽ�� ������"//"���������ļ�����ע�ͷ�, ��ͬ��չ���ļ�����ע�ͷ���config������
# "//#define xx yy " defineǰ�治�ܿո�, yy����һ��Ҫ�ǿո������β
# "//#if[n]def xx [...]" �� "//#platform xx [...]" ����β��ע�����Ƶ���
# "//##if[n]def xx [...]" �� "//##platform xx [...]" ������һ��ֱ��������֮ƥ���"//##endif"��"//##endplatform"
# ... ������define xx yy,define xx ,define xx, ���Ķ������Ᵽ��, defineǰ�治���пո� ��xx��yy֮��Ҫ�ո�, ��������ո�
# [...]����ʡ��
# Ҳ���԰ѿ�ע����Ϊ��ע��ʹ��, ���ﲢ���ϸ���
# ������ʹ��``��Χһ��token, �����defined��, ���Ѿ�define���ַ������. ���Զ��ʹ��

def readConfig():
  global config
  global platform
  global predefined
  global defined
  global process
  global extract
  global exclude

  if os.path.exists("config.repackage") and os.path.isfile("config.repackage"):
      h = open("config.repackage", "r")
  else:
    return False

  config = json.load(h)
  h.close()
  platform = config["platform"]
  predefined = config["defined"]
  predefined["platform"] = platform
  defined = copy.deepcopy(predefined)

  process = iniFileList(config["process"])

  try:
    exclude += iniFileList(config["exclude"][platform])
  except:
    print "WANING: exclude of platform", platform, "not defined"
  try:
    extract += iniFileList(config["extract"][platform])
  except:
    print "WANING: extract of platform", platform, "not defined"
  try:
    exclude += iniFileList(config["exclude"]["All"])
  except:
    print "WANING: exclude of All not defined"
  try:
    extract += iniFileList(config["extract"]["All"])
  except:
    print "WANING: extract of All not defined"
  return True

def iniFileList(list):
  l = []
  for i in list:
    s = expandFileName(i)
    re = toReg(s)
    l.append(re)
  return l

def toReg(i):
  return re.compile(i, re.I)

def iniConfigFile():
  h = open("config.repackage", "w")
  json.dump(config, h ,sort_keys=True, indent=4)
  h.close()

def expandFileName(name):
  name = trimFileName(projectDir)+ "/" + name.lower()
  return name

def trimFileName(file):
  s = file.lower()
  s = file.replace("\\", "/")
  return s

def trimFileNames(list):
  l = []
  for i in list:
    l.append(trimFileName(i))
  return l

def processFile(fileName):
  global config
  global platform
  global predefined
  global defined
  global process
  global extract
  global exclude
  global handled

  def checkBlock(lineparts, blockValid, wd):
    global handled
    if lineparts[1].startswith(wd):
      token = word.findall(lineparts[1][len(wd) + 1:])[0]
      if wd == "platform":
        blockValid.append(token == platform)
      else:
        blockValid.append(token in defined.keys())
      handled = True
    else:
      handled = False

  def checkLine(lineparts, wd):
    global handled
    if lineparts[1].startswith(wd):
      token = word.findall(lineparts[1][len(wd) + 1:])[0]
      handled = True
      if wd == "platform":
        return token == platform
      else:
        return token in defined.keys()
    else:
      return False

  def info(lnum, fileName, inf):
    print "info in", fileName, "line", lnum, inf

  def addDef(inst, defined, lnum, fileName):
    tmp = nonspace.findall(inst)
    if len(tmp) >= 2:
      if defined.has_key(tmp[1]):
        info (lnum, fileName, "redefine: " +  tmp[1])
    try:
      defined[tmp[1]] = tmp[2]
    except:
      try:
        defined[tmp[1]] = ""
      except:
        info(lnum, fileName, "define xx yy")

  def addDefs(lineparts, defined, lnum, fileName):
    if "[" in lineparts[1] and "]" in lineparts[1]:
      instructions = lineparts[1][lineparts[1].find("[") + 1: lineparts[1].find("]")]
      for inst in instructions.split(","):
        # ����define
        if "define" in inst:
          addDef(inst, defined, lnum, fileName)

  defined = copy.deepcopy(predefined)
  h = open(fileName, "r")
  cms = config["lineCommentBeginString"][getExt(fileName)]
  deleteComment = config["deleteComment"][getExt(fileName)]
  lines = h.readlines()
  trimedLines = []
  blockValid = []
  lnum = 0
  for line in lines:
    lnum += 1
    handled = False #��ʾ�п��ô�����
    defValid = False #��ʾ������ȷ, �����define���Ӧ�ñ�ִ��

    if blockValid:
      #isTrue�ǿ�, �ڿ��ƿ���
      if cms + "##end" in line:
        if blockValid[-1]:
          if deleteComment:
            trimedLines.append(line.split(cms + "##end")[0])
          else:
            trimedLines.append(line)
        blockValid.pop()
        continue  #������һ������
      elif not blockValid[-1]:
        continue

    #�����ڿ��ڿ���, �д����߼���ͬ
    lineparts = line.split(cms)
    line = lineparts[0]
    defParts = line.split("`")
    if len(defParts) % 2 == 0:
      info(lnum, fileName, "define not closed")
    else:
      i = 0
      for i in range(len(defParts) / 2):
        try:
          defParts[2 * i + 1] = defined[defParts[2 * i + 1]]
        except:
          defParts[2 * i + 1] = "`" + defParts[2 * i + 1] + "`"
    line = "".join(defParts)
    lineparts[0] = line
    line = cms.join(lineparts)

    if cms + "##" in line:
      #����ƿ�ʼ
      lineparts = line.split(cms + "##")
      checkBlock(lineparts, blockValid, "ifdef")
      checkBlock(lineparts, blockValid, "ifndef")
      checkBlock(lineparts, blockValid, "platform")
      defValid = blockValid[-1]
    elif cms + "#define" in line:
      lineparts = line.split(cms + "#")
      #���Ƶ���
      addDef(lineparts[1], defined, lnum, fileName)
    elif cms + "#" in line:
      lineparts = line.split(cms + "#")
      defValid |= checkLine(lineparts, "ifdef")
      defValid |= checkLine(lineparts, "ifndef")
      defValid |= checkLine(lineparts, "platform")
    else:
      lineparts = [line]

    if handled and defValid:
      addDefs(lineparts, defined, lnum, fileName)

    if not handled or defValid:
      if deleteComment:
        trimedLines.append(lineparts[0])
      else:
        trimedLines.append(line)

  return trimedLines

def getExt(fileName):
  s = ""
  try:
    s = fileName.split(".")[-1]
  except:
    s = ""
  return s

def work(root, exroot):
  root = trimFileName(root)
  exroot = trimFileName(exroot)

  if os.path.exists(exroot):
    filenames=os.listdir(exroot)
    if filenames:
      if raw_input(exroot + " not empty! go ahead anyway?[y/n]") != "y":
        return
      else:
        for f in filenames:
          f = exroot + "/" + f
          if os.path.isfile(f):
            os.remove(f)
            print f+" removed!"
          elif os.path.isdir(f):
            shutil.rmtree(f,True)
            print "dir "+f+" removed!"

  for dirpath, dirnames, filenames in os.walk(root):
    dirpath = trimFileName(dirpath)
    for filename in filenames:
      filename = dirpath + "/" + filename
      exFile = filename.replace(root, exroot)
      exDir = dirpath.replace(root, exroot)

      processed = False
      for m in process:
        if m.match(filename):
          if not os.path.exists(exDir):
            os.makedirs(exDir)
          h = open(exFile, "w")
          try:
            h.writelines(processFile(filename))
          except:
            pass
          h.close()
          processed = True
          print "processed", filename
          break
      if processed:
        continue

      for ex in extract:
        if ex.match(filename):
          excluded = False
          for exc in exclude:
            if exc.match(filename):
              excluded = True
              break
          if not excluded:
            processed = True
            if not os.path.exists(exDir):
              os.makedirs(exDir)
            shutil.copyfile(filename, filename.replace(root, exroot))
            print "extract", filename
          break
      if not processed:
        print "file", filename, "ignored"

if __name__ == "__main__":
  if not readConfig():
    iniConfigFile()
    print "��༭��Ŀ¼�µ�config.repackage�ļ�, ��Ϊ����, ���ٴ����б��ű�"
  else:
    work(os.getcwd(), "d:/extracted/" + config["platform"])
  print "done"

