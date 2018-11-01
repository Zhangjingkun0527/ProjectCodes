package com.moodlevideo.server.dal.model;

public class TeacherInfo
{
  private Integer id;
  private Integer courseid;
  private String name;
  private String gender;
  private String birth;
  private String level;
  private String email;
  private String style;
  private String link;
  
  public Integer getId()
  {
    return this.id;
  }
  
  public void setId(Integer id)
  {
    this.id = id;
  }
  
  public Integer getCourseid()
  {
    return this.courseid;
  }
  
  public void setCourseid(Integer courseid)
  {
    this.courseid = courseid;
  }
  
  public String getName()
  {
    return this.name;
  }
  
  public void setName(String name)
  {
    this.name = (name == null ? null : name.trim());
  }
  
  public String getGender()
  {
    return this.gender;
  }
  
  public void setGender(String gender)
  {
    this.gender = (gender == null ? null : gender.trim());
  }
  
  public String getBirth()
  {
    return this.birth;
  }
  
  public void setBirth(String birth)
  {
    this.birth = (birth == null ? null : birth.trim());
  }
  
  public String getLevel()
  {
    return this.level;
  }
  
  public void setLevel(String level)
  {
    this.level = (level == null ? null : level.trim());
  }
  
  public String getEmail()
  {
    return this.email;
  }
  
  public void setEmail(String email)
  {
    this.email = (email == null ? null : email.trim());
  }
  
  public String getStyle()
  {
    return this.style;
  }
  
  public void setStyle(String style)
  {
    this.style = (style == null ? null : style.trim());
  }
  
  public String getLink()
  {
    return this.link;
  }
  
  public void setLink(String link)
  {
    this.link = (link == null ? null : link.trim());
  }
}
