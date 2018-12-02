package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.TeacherInfo;

public abstract interface TeacherInfoMapper
{
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(TeacherInfo paramTeacherInfo);
  
  public abstract int insertSelective(TeacherInfo paramTeacherInfo);
  
  public abstract TeacherInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract int updateByPrimaryKeySelective(TeacherInfo paramTeacherInfo);
  
  public abstract int updateByPrimaryKey(TeacherInfo paramTeacherInfo);
}
