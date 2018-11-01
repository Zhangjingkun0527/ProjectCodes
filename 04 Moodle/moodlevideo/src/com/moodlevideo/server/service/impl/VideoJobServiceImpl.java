package com.moodlevideo.server.service.impl;

import com.moodlevideo.server.bo.StudentAndVideoInfo;
import com.moodlevideo.server.dal.mapper.BehaviorInfoMapper;
import com.moodlevideo.server.dal.mapper.DailytimeInfoMapper;
import com.moodlevideo.server.dal.mapper.PredictScoreIndexInfoMapper;
import com.moodlevideo.server.dal.mapper.PredictScoreInfoMapper;
import com.moodlevideo.server.dal.mapper.RecommendVideoIndexInfoMapper;
import com.moodlevideo.server.dal.mapper.RecommendVideoInfoMapper;
import com.moodlevideo.server.dal.mapper.SectionInfoMapper;
import com.moodlevideo.server.dal.mapper.StarRatingInfoMapper;
import com.moodlevideo.server.dal.mapper.StudentInfoMapper;
import com.moodlevideo.server.dal.mapper.TimeRankIndexInfoMapper;
import com.moodlevideo.server.dal.mapper.TimeRankInfoMapper;
import com.moodlevideo.server.dal.model.BehaviorInfo;
import com.moodlevideo.server.dal.model.DailytimeInfo;
import com.moodlevideo.server.dal.model.PredictScoreIndexInfo;
import com.moodlevideo.server.dal.model.PredictScoreInfo;
import com.moodlevideo.server.dal.model.RecommendVideoIndexInfo;
import com.moodlevideo.server.dal.model.RecommendVideoInfo;
import com.moodlevideo.server.dal.model.SectionInfo;
import com.moodlevideo.server.dal.model.StarRatingInfo;
import com.moodlevideo.server.dal.model.StudentInfo;
import com.moodlevideo.server.dal.model.TimeRankIndexInfo;
import com.moodlevideo.server.dal.model.TimeRankInfo;
import com.moodlevideo.server.service.IVideoJobService;
import com.moodlevideo.server.util.BllConstantEnum;
import com.moodlevideo.server.util.RestModel;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;

import javax.annotation.Resource;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.ModelAndView;

@Service("iVideoJobService")
public class VideoJobServiceImpl
  implements IVideoJobService
{
  private static Logger logger = LoggerFactory.getLogger(VideoJobServiceImpl.class);
  @Resource(name="studentInfoMapper")
  private StudentInfoMapper studentInfoMapper;
  @Resource(name="sectionInfoMapper")
  private SectionInfoMapper sectionInfoMapper;
  @Resource(name="starRatingInfoMapper")
  private StarRatingInfoMapper starRatingInfoMapper;
  @Resource(name="behaviorInfoMapper")
  private BehaviorInfoMapper behaviorInfoMapper;
  @Resource(name="timeRankIndexInfoMapper")
  private TimeRankIndexInfoMapper timeRankIndexInfoMapper;
  @Resource(name="timeRankInfoMapper")
  private TimeRankInfoMapper timeRankInfoMapper;
  @Resource(name="recommendVideoInfoMapper")
  private RecommendVideoInfoMapper recommendVideoInfoMapper;
  @Resource(name="recommendVideoIndexInfoMapper")
  private RecommendVideoIndexInfoMapper recommendVideoIndexInfoMapper;
  @Resource(name="DailytimeInfoMapper")
  private DailytimeInfoMapper dailytimeInfoMapper;
  @Resource(name="PredictScoreInfoMapper")
  private PredictScoreInfoMapper predictscoreInfoMapper;
  @Resource(name="PredictScoreIndexInfoMapper")
  private PredictScoreIndexInfoMapper predictscoreIndexInfoMapper;
  
  public ModelAndView getUserAndVideoInfo(StudentAndVideoInfo studentAndVideoInfo)
    throws Exception
  {
    ModelAndView mav = new ModelAndView("video");
    if (studentAndVideoInfo.getUserId() != null)
    {
      StudentInfo studentInfo = this.studentInfoMapper
        .selectByPrimaryKey(studentAndVideoInfo.getUserId());
      if (studentInfo != null)
      {
        int userid = Integer.parseInt(studentAndVideoInfo.getUserId());
        DailytimeInfo dailytimeInfo = this.dailytimeInfoMapper.selectByPrimaryKey(Integer.valueOf(userid));
        String oneTime = dailytimeInfo.getTime();
        
        String t = oneTime.substring(0, 2) + ":" + oneTime.substring(2, 4) + ":00";
        mav.addObject("daily_time", t);

        PredictScoreIndexInfo predictscoreIndexInfo=this.predictscoreIndexInfoMapper.selectByPredicttime();
        PredictScoreInfo predictscoreInfo=this.predictscoreInfoMapper.selectByUseridAndHappentime(studentAndVideoInfo.getUserId(),predictscoreIndexInfo.getPredicttime());
        String happen=predictscoreInfo.getHappentime().toString();
        //SimpleDateFormat sdf1= new SimpleDateFormat("EEE MMM dd HH:mm:ss z yyyy", Locale.US);
        //SimpleDateFormat sdf2= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        //Date d=sdf1.parse(happen);
        //String temptime=sdf2.format(sdf1.parse(happen));
        //logger.debug(temptime);
        mav.addObject("predict_time",happen);
        mav.addObject("click_time",predictscoreInfo.getClicktime());
        if(predictscoreInfo!=null)
        	mav.addObject("predict_score",predictscoreInfo.getScore());
        else
        	mav.addObject("predict_score","no data");
        
        
        mav.addObject("login_userid", studentInfo.getId());
        mav.addObject("login_username", studentInfo.getName());
        
        SectionInfo sectionInfo = this.sectionInfoMapper
          .selectByPrimaryKey(studentAndVideoInfo.getSectionId());
        if (sectionInfo != null)
        {
          mav.addObject("video_sectionid", sectionInfo.getSectionid());
          mav.addObject("video_url", sectionInfo.getUrl());
          mav.addObject("video_description", sectionInfo.getDescription());
          logger.debug("������UserAndVideoInfo����������++++++" + sectionInfo.getUrl().substring(0, 4));
          if (sectionInfo.getUrl().substring(0, 5).equals("beida")) {
            mav.addObject("video_moodle_url", "http://39.107.98.156/moodle/course/view.php?id=11");
          } else if (sectionInfo.getUrl().substring(0, 5).equals("zheda")) {
            mav.addObject("video_moodle_url", "http://39.107.98.156/moodle/course/view.php?id=23");
          } else if (sectionInfo.getUrl().substring(0, 5).equals("guofa")) {
            mav.addObject("video_moodle_url", "http://39.107.98.156/moodle/course/view.php?id=22");
          }
          logger.debug("������UserAndVideoInfo����������***������video_url����" + sectionInfo.getUrl());
          
          RecommendVideoIndexInfo recommendVideoIndexInfo = 
            this.recommendVideoIndexInfoMapper.selectByMaxPrimaryKey();
          
          ArrayList<RecommendVideoInfo> recommendVideoInfoList = 
            this.recommendVideoInfoMapper.selectByUseridAndUpdateid(
            studentInfo.getId(), recommendVideoIndexInfo.getUpdateId());
          
          ArrayList<HashMap<String, Object>> recommendList = 
            new ArrayList();
          for (RecommendVideoInfo recommendInfo : recommendVideoInfoList)
          {
            HashMap<String, Object> tempMap = new HashMap();
            tempMap.put("video_url", "/moodlevideo/videojob/section?sectionid=" + 
              recommendInfo.getVideoId());
            
            tempMap.put("video_description", recommendInfo.getVideoDescription());
            
            recommendList.add(tempMap);
          }
          logger.debug("������UserAndVideoInfo��������������������" + recommendList);
          mav.addObject("recommendList", recommendList);
        }
        else
        {
          mav.addObject("video_moodle_url", "http://120.77.86.170/moodle/my/");
          logger.debug("������UserAndVideoInfo����������***����������������sectionid������");
        }
        logger.debug("������UserAndVideoInfo����������***����������userId����" + studentInfo.getId());
        return mav;
      }
      logger.debug("������UserAndVideoInfo����������***����������������userId������");
    }
    return null;
  }
  
  public ModelAndView getVideoHtml(SectionInfo sectionInfo)
    throws Exception
  {
    ModelAndView mav = new ModelAndView("video");
    if (sectionInfo.getSectionid() != null)
    {
      sectionInfo = this.sectionInfoMapper.selectByPrimaryKey(
        sectionInfo.getSectionid());
      if (sectionInfo != null)
      {
        mav.addObject("video_url", sectionInfo.getUrl());
        mav.addObject("video_description", sectionInfo.getDescription());
        logger.debug("��������������������***������video_url����" + sectionInfo.getUrl());
      }
      else
      {
        logger.debug("��������������������***����������������sectionid������");
      }
    }
    return mav;
  }
  
  public RestModel videoStarRating(StarRatingInfo starRatingInfo)
  {
    RestModel restModel = new RestModel();
    int rflag = this.starRatingInfoMapper.insertSelective(starRatingInfo);
    if (rflag == 1)
    {
      restModel = RestModel.getRestModel(BllConstantEnum.RESCODE_0);
      logger.debug("������������***������������������");
    }
    else
    {
      restModel = RestModel.getRestModel(BllConstantEnum.RESCODE_1);
      logger.debug("������������***������������������");
    }
    return restModel;
  }
  
  public RestModel videoBehaviorRecord(BehaviorInfo behaviorInfo)
  {
    RestModel restModel = new RestModel();
    int rflag = this.behaviorInfoMapper.insertSelective(behaviorInfo);
    if (rflag == 1)
    {
      restModel = RestModel.getRestModel(BllConstantEnum.RESCODE_0);
      logger.debug("����������������***������������������");
    }
    else
    {
      restModel = RestModel.getRestModel(BllConstantEnum.RESCODE_1);
      logger.debug("����������������***������������������");
    }
    return restModel;
  }
  
  public RestModel getVideoRankData()
  {
    RestModel restModel = new RestModel();
    
    TimeRankIndexInfo timeRankIndexInfo = this.timeRankIndexInfoMapper.selectByMaxPrimaryKey();
    
    logger.debug("������������������������������***������updateId={}", timeRankIndexInfo.getUpdateId());
    
    ArrayList<TimeRankInfo> timeRankInfoList = this.timeRankInfoMapper.selectByUpdateId(
      timeRankIndexInfo.getUpdateId());
    
    ArrayList<HashMap<String, Object>> userRankList = 
      new ArrayList();
    for (TimeRankInfo timeRankInfo : timeRankInfoList)
    {
      HashMap<String, Object> tempMap = new HashMap();
      tempMap.put("userid", timeRankInfo.getUserid());
      tempMap.put("name", timeRankInfo.getName());
      if (timeRankInfo.getTotaltime() != null)
      {
        SimpleDateFormat formatter = new SimpleDateFormat("HH:mm:ss");
        tempMap.put("totaltime", formatter.format(timeRankInfo.getTotaltime()));
      }
      else
      {
        tempMap.put("totaltime", timeRankInfo.getTotaltime());
      }
      tempMap.put("rank", timeRankInfo.getRank());
      
      userRankList.add(tempMap);
    }
    HashMap<String, Object> jsonMap = new HashMap();
    SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    jsonMap.put("rankUpdateTime", formatter.format(timeRankIndexInfo.getUpdateTime()));
    jsonMap.put("userRank", userRankList);
    
    logger.debug("������������������������������***������json������{}", jsonMap);
    
    restModel = RestModel.getRestModel(BllConstantEnum.RESCODE_0, jsonMap);
    
    return restModel;
  }
  public String predictClickRecord(PredictScoreInfo paramPredictScoreInfo)
  {
	  PredictScoreIndexInfo predictscoreIndexInfo=this.predictscoreIndexInfoMapper.selectByPredicttime();
	  paramPredictScoreInfo.setHappentime(predictscoreIndexInfo.getPredicttime());
	  this.predictscoreInfoMapper.updateByHappentime(paramPredictScoreInfo);
	  return "update click_predict_time successfully";
	  
  }
}
