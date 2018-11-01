package com.moodlevideo.server.bo;

public class KnowledgeLessonMapInfo
{
  private String lessonId;
  private String sectionId;
  private float weight;
  
  public String getLessonId()
  {
    return this.lessonId;
  }
  
  public void setLessonId(String lessonId)
  {
    this.lessonId = lessonId;
  }
  
  public String getSectionId()
  {
    return this.sectionId;
  }
  
  public void setSectionId(String sectionId)
  {
    this.sectionId = sectionId;
  }
  
  public float getWeight()
  {
    return this.weight;
  }
  
  public void setWeight(float wight)
  {
    this.weight = wight;
  }
}
