package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.StudentInfo;

public abstract interface StudentInfoMapper
{
  public abstract int deleteByPrimaryKey(String paramString);
  
  public abstract int insert(StudentInfo paramStudentInfo);
  
  public abstract int insertSelective(StudentInfo paramStudentInfo);
  
  public abstract StudentInfo selectByPrimaryKey(String paramString);
  
  public abstract int updateByPrimaryKeySelective(StudentInfo paramStudentInfo);
  
  public abstract int updateByPrimaryKey(StudentInfo paramStudentInfo);
}
