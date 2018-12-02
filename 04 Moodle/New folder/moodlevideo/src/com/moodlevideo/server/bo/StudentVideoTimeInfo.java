package com.moodlevideo.server.bo;

public class StudentVideoTimeInfo
{
  private String sectionId;
  private String sectionTile;
  private int watchTime;
  private int videoTime;
  
  public String getSectionId()
  {
    return this.sectionId;
  }
  
  public void setSectionId(String sectionId)
  {
    this.sectionId = sectionId;
  }
  
  public String getSectionTile()
  {
    return this.sectionTile;
  }
  
  public void setSectionTile(String sectionTile)
  {
    this.sectionTile = sectionTile;
  }
  
  public int getWatchTime()
  {
    return this.watchTime;
  }
  
  public void setWatchTime(int watchTime)
  {
    this.watchTime = watchTime;
  }
  
  public int getVideoTime()
  {
    return this.videoTime;
  }
  
  public void setVideoTime(int videoTime)
  {
    this.videoTime = videoTime;
  }
}
