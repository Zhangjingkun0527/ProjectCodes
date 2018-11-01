package com.moodlevideo.server.dal.model;

import java.util.Date;

public class TimeRankInfo
{
  private Integer id;
  private String userid;
  private String updateId;
  private String name;
  private Date totaltime;
  private Integer rank;
  private String description;
  
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
  
  public String getUpdateId()
  {
    return this.updateId;
  }
  
  public void setUpdateId(String updateId)
  {
    this.updateId = (updateId == null ? null : updateId.trim());
  }
  
  public String getName()
  {
    return this.name;
  }
  
  public void setName(String name)
  {
    this.name = (name == null ? null : name.trim());
  }
  
  public Date getTotaltime()
  {
    return this.totaltime;
  }
  
  public void setTotaltime(Date totaltime)
  {
    this.totaltime = totaltime;
  }
  
  public Integer getRank()
  {
    return this.rank;
  }
  
  public void setRank(Integer rank)
  {
    this.rank = rank;
  }
  
  public String getDescription()
  {
    return this.description;
  }
  
  public void setDescription(String description)
  {
    this.description = (description == null ? null : description.trim());
  }
}
