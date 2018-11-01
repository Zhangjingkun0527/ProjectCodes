package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.LessonInfo;

public abstract interface LessonInfoMapper
{
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(LessonInfo paramLessonInfo);
  
  public abstract int insertSelective(LessonInfo paramLessonInfo);
  
  public abstract LessonInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract int updateByPrimaryKeySelective(LessonInfo paramLessonInfo);
  
  public abstract int updateByPrimaryKey(LessonInfo paramLessonInfo);
}
