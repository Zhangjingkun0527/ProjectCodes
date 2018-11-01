package com.moodlevideo.server.dal.mapper;

import java.util.Date;

import org.apache.ibatis.annotations.Param;

import com.moodlevideo.server.dal.model.PredictScoreIndexInfo;

public abstract interface PredictScoreIndexInfoMapper
{
	public abstract PredictScoreIndexInfo selectByPredicttime();
}
