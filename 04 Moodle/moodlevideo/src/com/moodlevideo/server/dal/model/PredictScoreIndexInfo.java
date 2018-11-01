package com.moodlevideo.server.dal.model;

import java.util.Date;

public class PredictScoreIndexInfo
{
  private Integer id;
  private Date predict_time;
  
  public Integer getId()
  {
    return this.id;
  }
  
  public void setId(Integer id)
  {
    this.id = id;
  }
  
  public Date getPredicttime()
  {
    return this.predict_time;
  }
  
  public void setHappentime(Date predict_time)
  {
    this.predict_time = predict_time;
  }
}
