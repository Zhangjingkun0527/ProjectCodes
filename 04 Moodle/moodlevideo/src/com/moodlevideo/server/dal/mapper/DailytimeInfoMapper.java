package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.DailytimeInfo;

public abstract interface DailytimeInfoMapper
{
  public abstract DailytimeInfo selectByPrimaryKey(Integer paramInteger);
}
