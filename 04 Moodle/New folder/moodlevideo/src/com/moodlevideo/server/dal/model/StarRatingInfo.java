package com.moodlevideo.server.dal.model;

import java.util.Date;

public class StarRatingInfo
{
  private Integer id;
  private String userid;
  private String sectionid;
  private Float grade;
  private String videotime;
  private Date happentime;
  
  public Integer getId()
  {
    return this.id;
  }
  
  public void setId(Integer id)
  {
    this.id = id;
  }
  
  public String getUserid()
  {
    return this.userid;
  }
  
  public void setUserid(String userid)
  {
    this.userid = (userid == null ? null : userid.trim());
  }
  
  public String getSectionid()
  {
    return this.sectionid;
  }
  
  public void setSectionid(String sectionid)
  {
    this.sectionid = (sectionid == null ? null : sectionid.trim());
  }
  
  public Float getGrade()
  {
    return this.grade;
  }
  
  public void setGrade(Float grade)
  {
    this.grade = grade;
  }
  
  public String getVideotime()
  {
    return this.videotime;
  }
  
  public void setVideotime(String videotime)
  {
    this.videotime = (videotime == null ? null : videotime.trim());
  }
  
  public Date getHappentime()
  {
    return this.happentime;
  }
  
  public void setHappentime(Date happentime)
  {
    this.happentime = happentime;
  }
}
