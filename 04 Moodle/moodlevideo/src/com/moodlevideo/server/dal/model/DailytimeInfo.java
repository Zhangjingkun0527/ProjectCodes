package com.moodlevideo.server.dal.model;

public class DailytimeInfo
{
  private int id;
  private String time;
  
  public Integer getId()
  {
    return Integer.valueOf(this.id);
  }
  
  public void setId(Integer id)
  {
    this.id = id.intValue();
  }
  
  public String getTime()
  {
    return this.time;
  }
  
  public void setTime(String time)
  {
    this.time = time;
  }
}
