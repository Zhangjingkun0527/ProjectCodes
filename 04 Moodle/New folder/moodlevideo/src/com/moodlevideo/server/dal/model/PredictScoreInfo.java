package com.moodlevideo.server.dal.model;

import java.util.Date;

public class PredictScoreInfo
{
  private Integer id;
  private String userid;
  private Integer score;
  private Date happentime;
  private Date clicktime;
  
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
  
  public Integer getScore()
  {
    return this.score;
  }
  
  public void setScore(Integer score)
  {
    this.score = score;
  }
  
  public Date getHappentime()
  {
    return this.happentime;
  }
  
  public void setHappentime(Date happentime)
  {
    this.happentime = happentime;
  }
  
  public Date getClicktime()
  {
    return this.clicktime;
  }
  
  public void setClicktime(Date clicktime)
  {
    this.clicktime = clicktime;
  }
}
