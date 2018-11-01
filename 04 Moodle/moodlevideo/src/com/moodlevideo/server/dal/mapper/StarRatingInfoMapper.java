package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.StarRatingInfo;

public abstract interface StarRatingInfoMapper
{
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(StarRatingInfo paramStarRatingInfo);
  
  public abstract int insertSelective(StarRatingInfo paramStarRatingInfo);
  
  public abstract StarRatingInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract int updateByPrimaryKeySelective(StarRatingInfo paramStarRatingInfo);
  
  public abstract int updateByPrimaryKey(StarRatingInfo paramStarRatingInfo);
}
