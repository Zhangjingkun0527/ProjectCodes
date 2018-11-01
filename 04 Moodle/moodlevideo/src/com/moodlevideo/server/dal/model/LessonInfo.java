package com.moodlevideo.server.dal.model;

public class LessonInfo
{
  private Integer id;
  private Integer courseid;
  private Byte chapter;
  private Byte section;
  private String videotime;
  private String style;
  private String subject;
  private String keyword;
  private Byte difficulty;
  private Integer teacherid;
  private Byte accuracy;
  private String gesture;
  private String blackboardWriting;
  private String guidance;
  private String example;
  private String macroscopicView;
  private String microcosmicView;
  private String note;
  private Byte speed;
  private Byte noise;
  private Byte joke;
  private String url;
  
  public Integer getId()
  {
    return this.id;
  }
  
  public void setId(Integer id)
  {
    this.id = id;
  }
  
  public Integer getCourseid()
  {
    return this.courseid;
  }
  
  public void setCourseid(Integer courseid)
  {
    this.courseid = courseid;
  }
  
  public Byte getChapter()
  {
    return this.chapter;
  }
  
  public void setChapter(Byte chapter)
  {
    this.chapter = chapter;
  }
  
  public Byte getSection()
  {
    return this.section;
  }
  
  public void setSection(Byte section)
  {
    this.section = section;
  }
  
  public String getVideotime()
  {
    return this.videotime;
  }
  
  public void setVideotime(String videotime)
  {
    this.videotime = (videotime == null ? null : videotime.trim());
  }
  
  public String getStyle()
  {
    return this.style;
  }
  
  public void setStyle(String style)
  {
    this.style = (style == null ? null : style.trim());
  }
  
  public String getSubject()
  {
    return this.subject;
  }
  
  public void setSubject(String subject)
  {
    this.subject = (subject == null ? null : subject.trim());
  }
  
  public String getKeyword()
  {
    return this.keyword;
  }
  
  public void setKeyword(String keyword)
  {
    this.keyword = (keyword == null ? null : keyword.trim());
  }
  
  public Byte getDifficulty()
  {
    return this.difficulty;
  }
  
  public void setDifficulty(Byte difficulty)
  {
    this.difficulty = difficulty;
  }
  
  public Integer getTeacherid()
  {
    return this.teacherid;
  }
  
  public void setTeacherid(Integer teacherid)
  {
    this.teacherid = teacherid;
  }
  
  public Byte getAccuracy()
  {
    return this.accuracy;
  }
  
  public void setAccuracy(Byte accuracy)
  {
    this.accuracy = accuracy;
  }
  
  public String getGesture()
  {
    return this.gesture;
  }
  
  public void setGesture(String gesture)
  {
    this.gesture = (gesture == null ? null : gesture.trim());
  }
  
  public String getBlackboardWriting()
  {
    return this.blackboardWriting;
  }
  
  public void setBlackboardWriting(String blackboardWriting)
  {
    this.blackboardWriting = (blackboardWriting == null ? null : blackboardWriting.trim());
  }
  
  public String getGuidance()
  {
    return this.guidance;
  }
  
  public void setGuidance(String guidance)
  {
    this.guidance = (guidance == null ? null : guidance.trim());
  }
  
  public String getExample()
  {
    return this.example;
  }
  
  public void setExample(String example)
  {
    this.example = (example == null ? null : example.trim());
  }
  
  public String getMacroscopicView()
  {
    return this.macroscopicView;
  }
  
  public void setMacroscopicView(String macroscopicView)
  {
    this.macroscopicView = (macroscopicView == null ? null : macroscopicView.trim());
  }
  
  public String getMicrocosmicView()
  {
    return this.microcosmicView;
  }
  
  public void setMicrocosmicView(String microcosmicView)
  {
    this.microcosmicView = (microcosmicView == null ? null : microcosmicView.trim());
  }
  
  public String getNote()
  {
    return this.note;
  }
  
  public void setNote(String note)
  {
    this.note = (note == null ? null : note.trim());
  }
  
  public Byte getSpeed()
  {
    return this.speed;
  }
  
  public void setSpeed(Byte speed)
  {
    this.speed = speed;
  }
  
  public Byte getNoise()
  {
    return this.noise;
  }
  
  public void setNoise(Byte noise)
  {
    this.noise = noise;
  }
  
  public Byte getJoke()
  {
    return this.joke;
  }
  
  public void setJoke(Byte joke)
  {
    this.joke = joke;
  }
  
  public String getUrl()
  {
    return this.url;
  }
  
  public void setUrl(String url)
  {
    this.url = (url == null ? null : url.trim());
  }
}
