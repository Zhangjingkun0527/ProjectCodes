package com.moodlevideo.server.dal.model;

import java.util.Date;

public class BehaviorInfo
{
  private Integer id;
  private String userid;
  private String sectionid;
  private Integer behave;
  private String starttime;
  private String endtime;
  private String duration;
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
  
  public Integer getBehave()
  {
    return this.behave;
  }
  
  public void setBehave(Integer behave)
  {
    this.behave = behave;
  }
  
  public String getStarttime()
  {
    return this.starttime;
  }
  
  public void setStarttime(String starttime)
  {
    this.starttime = (starttime == null ? null : starttime.trim());
  }
  
  public String getEndtime()
  {
    return this.endtime;
  }
  
  public void setEndtime(String endtime)
  {
    this.endtime = (endtime == null ? null : endtime.trim());
  }
  
  public String getDuration()
  {
    return this.duration;
  }
  
  public void setDuration(String duration)
  {
    this.duration = (duration == null ? null : duration.trim());
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
