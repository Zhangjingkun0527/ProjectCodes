package com.moodlevideo.server.dal.model;

public class RecommendVideoInfo
{
  private Integer id;
  private String userid;
  private String updateId;
  private String videoId;
  private String videoDescription;
  
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
  
  public String getVideoId()
  {
    return this.videoId;
  }
  
  public void setVideoId(String videoId)
  {
    this.videoId = (videoId == null ? null : videoId.trim());
  }
  
  public String getVideoDescription()
  {
    return this.videoDescription;
  }
  
  public void setVideoDescription(String videoDescription)
  {
    this.videoDescription = (videoDescription == null ? null : videoDescription.trim());
  }
}
