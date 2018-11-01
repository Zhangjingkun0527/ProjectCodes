package com.moodlevideo.server.bo;

public class StudentAndVideoInfo
{
  private String userId;
  private String password;
  private String sectionId;
  
  public String getUserId()
  {
    return this.userId;
  }
  
  public void setUserId(String userId)
  {
    this.userId = userId;
  }
  
  public String getPassword()
  {
    return this.password;
  }
  
  public void setPassword(String password)
  {
    this.password = password;
  }
  
  public String getSectionId()
  {
    return this.sectionId;
  }
  
  public void setSectionId(String sectionId)
  {
    this.sectionId = sectionId;
  }
}
