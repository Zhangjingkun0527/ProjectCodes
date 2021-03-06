package com.moodlevideo.server.dal.model;

import java.util.Date;

public class TimeRankIndexInfo
{
  private String updateId;
  private Date updateTime;
  private String description;
  
  public String getUpdateId()
  {
    return this.updateId;
  }
  
  public void setUpdateId(String updateId)
  {
    this.updateId = (updateId == null ? null : updateId.trim());
  }
  
  public Date getUpdateTime()
  {
    return this.updateTime;
  }
  
  public void setUpdateTime(Date updateTime)
  {
    this.updateTime = updateTime;
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
