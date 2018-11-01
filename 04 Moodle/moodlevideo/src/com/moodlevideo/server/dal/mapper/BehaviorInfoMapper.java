package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.BehaviorInfo;

public abstract interface BehaviorInfoMapper
{
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(BehaviorInfo paramBehaviorInfo);
  
  public abstract int insertSelective(BehaviorInfo paramBehaviorInfo);
  
  public abstract BehaviorInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract int updateByPrimaryKeySelective(BehaviorInfo paramBehaviorInfo);
  
  public abstract int updateByPrimaryKey(BehaviorInfo paramBehaviorInfo);
}
