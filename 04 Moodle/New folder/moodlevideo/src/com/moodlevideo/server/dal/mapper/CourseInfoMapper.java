package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.CourseInfo;

public abstract interface CourseInfoMapper
{
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(CourseInfo paramCourseInfo);
  
  public abstract int insertSelective(CourseInfo paramCourseInfo);
  
  public abstract CourseInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract int updateByPrimaryKeySelective(CourseInfo paramCourseInfo);
  
  public abstract int updateByPrimaryKey(CourseInfo paramCourseInfo);
}
