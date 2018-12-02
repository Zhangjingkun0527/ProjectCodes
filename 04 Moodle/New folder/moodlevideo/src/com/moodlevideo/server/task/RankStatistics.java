package com.moodlevideo.server.task;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.moodlevideo.server.bo.TimeRankInfo;
import com.moodlevideo.server.dal.model.BehaviorInfo;
import com.moodlevideo.server.dal.model.TimeRankIndexInfo;

/**
 * @author wangxuebin
 * 鐢ㄤ簬璁＄畻鐩稿簲瀛︾敓鎵�鏈夎鐪嬭棰戠殑瑙傜湅鏃堕棿
 */
public class RankStatistics {
	
	private static Logger logger = LoggerFactory
			.getLogger(RankStatistics.class);
	
	private static boolean SAVE_DATA_SWITCH = true;
	

	// 璁＄畻姣忎釜瀛︾敓涓�鍛ㄨ鐪嬭棰戠殑鏃堕棿,鎺掑簭骞跺瓨鍏ユ暟鎹簱鐩稿簲琛ㄤ腑
	public static void rankComputing(){
		// 鑾峰彇褰撴棩鐨勬棩鏈熸椂闂�
		Date now_date = new Date();
//		SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//		String date_str = "2017-04-05 11:59:59";
//		Date now_date = null;
//		try {
//			now_date = sdf1.parse(date_str);
//		} catch (ParseException e1) {
//			e1.printStackTrace();
//		}
		
		
		// 鍒濆鍖杢ime_rank_index鐨勪俊鎭�
		TimeRankIndexInfo timeRankIndexInfo = new TimeRankIndexInfo();
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmm");
		timeRankIndexInfo.setUpdateId( sdf.format(now_date) );
		sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:00");
		try { // 灏哢pdateTime鐨勭鏁颁綅缃负0
			now_date = sdf.parse( sdf.format(now_date) );
		} catch (ParseException e) {
			e.printStackTrace();
		}
		timeRankIndexInfo.setUpdateTime( now_date );
		logger.debug("銆愭洿鏂癡ideoTimeRank璁″垝task鏈嶅姟銆慯^^^TimeRankIndex^^^^"
			+ " updateId=" + timeRankIndexInfo.getUpdateId() 
			+ "    updateTime=" + timeRankIndexInfo.getUpdateTime() );
		
		// 鍔犺浇behavior鏁版嵁琛ㄥ苟璁＄畻寰楀埌鍚勪釜瀛︾敓鐨勮棰戣鐪嬫椂闂村璞″垪琛�(timeRankInfoList)
		ArrayList<TimeRankInfo> timeRankInfoList = loadBehaviorInfoAndGetTimeRankInfoList
				(timeRankIndexInfo, now_date);
		
		// 鎸塼otaltime澶у皬杩涜鎺掑簭
		Comparator<TimeRankInfo> comp = new ComparatorImpl();
		Collections.sort(timeRankInfoList, comp);
		for(int i=0; i<timeRankInfoList.size(); ++i){
			timeRankInfoList.get(i).setRank(i+1); // 璁剧疆鎺掑悕rank瀛楁
			if( i>0 && timeRankInfoList.get(i).getTotaltime()
				.equals(timeRankInfoList.get(i-1).getTotaltime()) ){
				// 纭繚鏃堕棿鐩稿悓鐨勫悓瀛︽帓鍚嶇浉鍚�
				timeRankInfoList.get(i).setRank(timeRankInfoList.get(i-1).getRank());
			}
			
		}
		
		
		logger.debug("銆愭洿鏂癡ideoTimeRank璁″垝task鏈嶅姟銆�*** 鎵�鏈夌敤鎴疯鐪嬫椂闂磋绠楀畬姣曪紝寮�濮嬪鍏ユ暟鎹簱...");
		boolean save_flag = true;
		if(SAVE_DATA_SWITCH){
			save_flag = saveTimeRankInfo(timeRankIndexInfo, timeRankInfoList);
		}
		if(save_flag){
			logger.debug("銆愭洿鏂癡ideoTimeRank璁″垝task鏈嶅姟銆�*** proccess excute successed!");
		} else {
			logger.debug("銆愭洿鏂癡ideoTimeRank璁″垝task鏈嶅姟銆�*** proccess excute failed!");
		}
		
	}
	
	/**
	 * 浠庢暟鎹簱涓姞杞絙ehavior鏁版嵁琛紝
	 * 骞惰绠楀緱鍒板悇涓鐢熺殑瑙嗛瑙傜湅鏃堕棿瀵硅薄鍒楄〃(timeRankInfoList)
	 * @param timeRankIndexInfo
	 * @param now_date
	 * @return behaviorInfoList
	 */
	private static ArrayList<TimeRankInfo> loadBehaviorInfoAndGetTimeRankInfoList
		(TimeRankIndexInfo timeRankIndexInfo, Date now_date){
		
		ArrayList<TimeRankInfo> timeRankInfoList = new ArrayList<TimeRankInfo>();	
		DBcon dBcon = new DBcon();
		
		// 鏌ヨ鏁版嵁搴撲腑瀛︾敓琛ㄧ殑淇℃伅,鍒濆鍖杢imeRankInfo灞�閮ㄤ俊鎭�
		String sql = "select * from student;";
		ResultSet rs = dBcon.Query(sql);
		try{
			while(rs.next()){// 鍒ゆ柇鏄惁杩樻湁涓嬩竴涓暟鎹�
				
				if(rs.getString("id").equals("1601210100")
				|| rs.getString("id").equals("1601210101")){
					continue; // 蹇界暐涓や釜娴嬭瘯璐﹀彿
				}
				TimeRankInfo timeRankInfo = new TimeRankInfo();
				timeRankInfo.setUserid( rs.getString("id") ); // 鍔犺浇瀛︾敓瀛﹀彿
				timeRankInfo.setName( rs.getString("name") ); // 鍔犺浇瀛︾敓濮撳悕
				timeRankInfo.setUpdateId( timeRankIndexInfo.getUpdateId() ); // 鍔犺浇update_id
				timeRankInfoList.add(timeRankInfo);
				
			}
		 }catch (SQLException e) {
			 e.printStackTrace();
		 }finally {
			dBcon.close();
		}
		
		// 鑾峰彇涓婁竴涓粺璁℃椂闂寸偣鐨勫叿浣撴棩鏈熸椂闂�
		String last_week_deadline = getLastWednesdayDate(now_date);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		// 瀵规瘡涓鍙峰鐢熷搴旂殑琛屼负鎿嶄綔杩涜缁熻璁＄畻鏃堕棿
		for(TimeRankInfo timeRankInfo : timeRankInfoList){
			
			ArrayList<BehaviorInfo> behaviorInfoList = new ArrayList<BehaviorInfo>();
			sql = "select * from behavior where userid='" 
				+ timeRankInfo.getUserid()
				+ "' and happentime>='" + last_week_deadline +"'"
				+ " and happentime<'" + sdf.format(now_date) + "'";
			rs = dBcon.Query(sql);
			try{
				// 鑾峰彇鐩稿簲userid鐢ㄦ埛鐨勬墍鏈夎涓轰俊鎭�
				while(rs.next()){
					BehaviorInfo behaviorInfo = new BehaviorInfo();
					behaviorInfo.setId( rs.getInt("id") );  // 璁板綍椤哄簭鏍囧彿id
					behaviorInfo.setUserid( rs.getString("userid") );  // 鐢ㄦ埛ID
					behaviorInfo.setSectionid( rs.getString("sectionid") ); // 璇剧▼灏忚妭ID
					behaviorInfo.setBehave( rs.getInt("behave") );     // 琛屼负鏍囧彿
					behaviorInfo.setStarttime( rs.getString("starttime") ); // 琛屼负寮�濮嬫椂闂�
					behaviorInfo.setEndtime( rs.getString("endtime") );     // 琛屼负缁撴潫鏃堕棿
					behaviorInfo.setDuration( rs.getString("duration") );   // 椤甸潰鎵撳紑鎸佺画鏃堕棿
					behaviorInfo.setHappentime( rs.getTimestamp("happentime") ); // 琛屼负鍙戠敓鏃堕棿
					behaviorInfoList.add(behaviorInfo);
				}
			 }catch (SQLException e) {
				 e.printStackTrace();
			 }finally {
				dBcon.close();
			}
			
			
			// 鑾峰彇缁熻鏃堕棿瀛楃涓�
			String time_str = student_statistics(behaviorInfoList);
			SimpleDateFormat sdf_parse=new SimpleDateFormat("HH:mm:ss");//灏忓啓鐨刴m琛ㄧず鐨勬槸鍒嗛挓   
			Date totaltime=null;
			try {
				totaltime = sdf_parse.parse(time_str);
			} catch (ParseException e) {
				e.printStackTrace();
			}
			timeRankInfo.setTotaltime(totaltime); // 璁剧疆timeRankInfo鐨則otaltime瀛楁
			
		}
		
		return timeRankInfoList;
	}
	
	/**
	 * 灏唗imeRankIndexInfo鐨勭浉鍏充俊鎭�
	 * 瀛樺叆鏁版嵁搴撶殑鐩稿簲鏁版嵁琛�
	 * @param timeRankIndexInfo
	 * @param timeRankInfoList
	 * @return behaviorInfoList
	 */
	private static boolean saveTimeRankInfo(TimeRankIndexInfo timeRankIndexInfo,
			ArrayList<TimeRankInfo> timeRankInfoList){
		
		boolean flag;
		DBcon dBcon = new DBcon();
		
		String sql = "insert into time_rank_index (update_id, update_time)"
				+ " VALUES ('" + timeRankIndexInfo.getUpdateId() 
				+ "','" + new Timestamp(timeRankIndexInfo.getUpdateTime().getTime()) + "');";
		
		flag = dBcon.Update(sql);
		if(!flag) return flag;
		
		for(TimeRankInfo timeRankInfo : timeRankInfoList){
			sql = "insert into time_rank (userid, update_id, name, totaltime, rank)"
					+ " VALUES ('" + timeRankInfo.getUserid()
					+ "','" + timeRankInfo.getUpdateId()
					+ "','" + timeRankInfo.getName()
					+ "','" + new Timestamp(timeRankInfo.getTotaltime().getTime())
					+ "','" + timeRankInfo.getRank()
					+ "');";
			
			flag = dBcon.Update(sql);
			if(!flag) return flag;
		}
		
		
		return true;
	}
	
	
	// 缁熻姣忎釜瀛︾敓鐨勮鐪嬫椂闂�
	private static String student_statistics(ArrayList<BehaviorInfo> behaviorInfoList){
		
		boolean flag_behave03=false, flag_behave07=false,
				flag_behave15=false, flag_behave16=false,
				flag_behave_start = false;
		int stat_time_sum = 0; // 鎬荤殑瑙傜湅鏃堕棿
		int behave_time_03 = 0,
			behave_time_07 = 0, behave_time_15 = 0,
			behave_time_16 = 0, behave_time_start = 0;
		int temp_sum = 0; // 鍗曟瑙傜湅浜嬩欢鐨勬椂闂�
		
		for(BehaviorInfo be: behaviorInfoList){
			
			// behave涓�1鎴�7鏍囧織鐫�缁撴潫涓�涓鐪嬩簨浠�
			if(be.getBehave()==1 || be.getBehave()==7){
				
				if(be.getBehave()==7){
					flag_behave07 = true;
					behave_time_07 = timeStrToSecondInt(be.getDuration());
				}
				
				// 浠ユ渶鍚庝竴涓棰戠粨鏉熸椂闂村拰鏈�鍚庝竴涓績璺冲寘鐨勬椂闂翠腑锛�
				// 杈冨ぇ鑰呬负瑙嗛瑙傜湅鏈�缁堟椂闂�
				if(flag_behave15 || flag_behave16){
					int bigger_time = behave_time_15;
					if(behave_time_15 < behave_time_16){
						bigger_time = behave_time_16;
					}
					temp_sum += bigger_time - behave_time_start;
					
				} else if(flag_behave07){ // 鍐嶆病鏈夛紝鍒欎互鍏抽棴椤甸潰鐨勬椂闂翠负鍑�
					temp_sum += behave_time_07 - behave_time_start;
					if(flag_behave03){
						// 瑙嗛瀹為檯瑙傜湅涓嶈冻涓ゅ垎閽熼暱鏃堕棿鏆傚仠
						temp_sum -= behave_time_07-behave_time_03;
					}
					
				}else {
					temp_sum = 0;
					if(flag_behave_start){
						// 鍙涓�涓棰戠偣寮�杩囧紑濮嬶紙涓嶈冻涓ゅ垎閽燂級锛岀畻40s琛ュ伩鏃堕棿
						// 浠ラ槻姝㈠嚭鐜拌鐪嬩簡鍑犱釜鐭棰戯紝浣嗘渶缁堣鐪嬭棰戞椂闂翠负0鐨勬儏鍐�
						temp_sum = 40; 
					}
					
				}
				
				if(!flag_behave_start){ // 浠庢病鏈夌偣寮�濮嬮敭
					temp_sum = 0;
				}
				stat_time_sum += temp_sum; // 涓�娆′簨浠剁殑鏃堕棿鍔犲埌鎬绘椂闂翠腑
				
				// 鏍囪瘑鍙橀噺缃�0
				temp_sum  = behave_time_07 = behave_time_15 
				= behave_time_16 = behave_time_start = 0;
				flag_behave_start = flag_behave07 = flag_behave03
				= flag_behave15 = flag_behave16 = false;
			}
			
			// 鑻ュ綋鍓嶆槸鏆傚仠鐘舵�侊紝鍒欎笉鑰冭檻鍏朵粬鎿嶄綔娑夊強鐨勬椂闂寸偣锛堜緥濡傝涓�8锛岄殣钘忛〉闈細娑夊強鏆傚仠鎿嶄綔锛�
			if(flag_behave03 && be.getBehave()!=2){
				continue;
			}
			
			// 鐐瑰嚮鈥樺紑濮嬧�欒涓哄鐞�
			if(be.getBehave()==2){  
				// 绗竴娆＄偣鍑诲紑濮�,浣滀负寮�濮嬭鐪嬭棰戠殑鏃堕棿鑺傜偣
				if(!flag_behave_start){
					flag_behave_start = true;
					behave_time_start = timeStrToSecondInt(be.getDuration());
					flag_behave03 = false; // 闃叉绗竴娆＄偣寮�濮嬪墠鏈�8琛屼负锛堟殏鍋滅殑涓�绉嶏級鎿嶄綔瀛樺湪
				} else if(flag_behave03){ // 闈炵涓�娆★紝涓斾箣鍓嶆湁杩囨殏鍋滄搷浣�
					temp_sum -= timeStrToSecondInt(be.getDuration()) - behave_time_03;
					flag_behave03 = false;

				}
				// 鍙閬囧埌2琛屼负锛屽氨鏇存柊16蹇冭烦鍖呯殑鏃堕棿
				// 浠ラ槻姝㈠嚭鐜版渶鍚庢椂闂存瘮鎵ｉ櫎鏃堕棿灏戠殑鎯呭喌
				flag_behave16 = true;
				behave_time_16 = timeStrToSecondInt(be.getDuration());
			}
			
			// 娑夊強鍒版椂闂存殏鍋滅殑鐩稿叧琛屼负鐨勬搷浣滃鐞�
			if(be.getBehave()==3
			|| be.getBehave()==8
			|| be.getBehave()==15){
				flag_behave03 = true;
				behave_time_03 = timeStrToSecondInt(be.getDuration());
				
				if(be.getBehave()==15){ // 鏇存柊鏈�鍚庝竴娆＄殑瑙嗛缁撴潫鏃堕棿
					flag_behave15 = true;
					behave_time_15 = timeStrToSecondInt(be.getDuration());
				}
			}
			
			// 鏇存柊鏈�鍚庝竴娆＄殑蹇冭烦鍖呮椂闂�
			if(be.getBehave()==16){ 
				flag_behave16 = true;
				behave_time_16 = timeStrToSecondInt(be.getDuration());

			}
			
		}
		
		// 鏈�鍚庝竴娆′簨浠舵病鏈変互7鎴�1缁撴潫锛岄渶鐗规畩澶勭悊
		if(flag_behave15 || flag_behave16){
			// 浠ユ渶鍚庝竴涓棰戠粨鏉熸椂闂村拰鏈�鍚庝竴涓績璺冲寘鐨勬椂闂翠腑锛�
			// 杈冨ぇ鑰呬负瑙嗛瑙傜湅鏈�缁堟椂闂�
			int bigger_time = behave_time_15;
			if(behave_time_15 < behave_time_16){
				bigger_time = behave_time_16;
			}
			temp_sum += bigger_time - behave_time_start;
			
		} else {
			temp_sum = 0;
			if(flag_behave_start){
				// 鍙涓�涓棰戠偣寮�杩囧紑濮嬶紙涓嶈冻涓ゅ垎閽燂級锛岀畻40s琛ュ伩鏃堕棿
				// 浠ラ槻姝㈠嚭鐜拌鐪嬩簡鍑犱釜鐭棰戯紝浣嗘渶缁堣鐪嬭棰戞椂闂翠负0鐨勬儏鍐�
				temp_sum = 40; 
			}
		}
		stat_time_sum += temp_sum; // 鏈�鍚庝竴娆′簨浠剁殑鏃堕棿鍔犲埌鎬绘椂闂翠腑
		
		
		return secondIntToTimeStr(stat_time_sum);
	}
	
	
	// 灏嗘椂闂村瓧绗︿覆杞寲涓篒nt鍨嬬殑绉掓暟
	private static int timeStrToSecondInt(String timeStr){
		int minutes =0, seconds = 0;
		if(timeStr.length()==5){ // 00:00
			minutes = Integer.parseInt(timeStr.substring(0, 2));
			seconds = Integer.parseInt(timeStr.substring(3, 5));
		} else if(timeStr.length()==6){ // 000:00
			minutes = Integer.parseInt(timeStr.substring(0, 3));
			seconds = Integer.parseInt(timeStr.substring(4, 6));
		} else if(timeStr.length()==7){ // 0000:00
			minutes = Integer.parseInt(timeStr.substring(0, 4));
			seconds = Integer.parseInt(timeStr.substring(5, 7));
		}
		
		return minutes*60+seconds;
	}
	
	// 灏咺nt鍨嬬殑绉掓暟杞寲涓烘爣鍑嗘椂闂村瓧绗︿覆
	private static String secondIntToTimeStr(int time){
		
		String hours = String.valueOf(time / 3600);
		String minutes = String.valueOf(time % 3600 / 60);
		String seconds = String.valueOf(time % 60);
		
		if(hours.length()==0){
			hours = "00";
		} else if(hours.length()==1){
			hours = "0" + hours;
		}
		if(minutes.length()==0){
			minutes = "00";
		} else if(minutes.length()==1){
			minutes = "0" + minutes;
		}
		if(seconds.length()==0){
			seconds = "00";
		} else if(seconds.length()==1){
			seconds = "0" + seconds;
		}
		
		String timestr = hours + ":" + minutes + ":" + seconds;
		
		
		return timestr;
	}
	
	
	// 鑾峰彇鏈�杩戠殑涓�涓粺璁¤妭鐐圭殑鏃ユ湡鏃堕棿锛堜笂鍛ㄤ笁鎴栨湰鍛ㄤ笁锛�
	@SuppressWarnings("deprecation")
	private static String getLastWednesdayDate(Date date){
		
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		// 杞鑾峰彇涓婂懆涓夌殑鍏蜂綋鏃ユ湡
		cal.add(Calendar.DAY_OF_WEEK, -1); 
        while (cal.get(Calendar.DAY_OF_WEEK) != Calendar.WEDNESDAY) {
            cal.add(Calendar.DAY_OF_WEEK, -1); 
        }
		
		if(date.getDay()==3 && date.getHours()>=12) { 
			// 褰撴棩濡傛灉鏄懆涓夛紝鍒欏垽鏂槸鍚﹁繃浜嗕腑鍗堝崄浜岀偣
			cal.setTime(date); // 瓒呰繃鍗佷簩鐐瑰垯鎸変粖澶╂棩鏈熶负鍩哄噯锛屽惁鍒欐寜涓婂懆涓夋棩鏈熶负鍩哄噯
		}
		
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
		String dateStr = sdf.format(cal.getTime());
		String wednesdayDateStr = dateStr + " 12:00:00"; // 鎷兼帴涓婂懆涓夋棩鏈熸椂闂村瓧绗︿覆
		
//		sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//		Date wednesdayDate = null;
//		try { // 寰楀埌涓婂懆涓夌殑鍏蜂綋鏃ユ湡
//			wednesdayDate = sdf.parse(wednesdayDateStr);
//		} catch (ParseException e) {
//			e.printStackTrace();
//		}
		
		return wednesdayDateStr;
	}
	

}

// 姣旇緝绫�
class ComparatorImpl implements Comparator<TimeRankInfo> {
	
	public int compare(TimeRankInfo tr1, TimeRankInfo tr2) {
		int s1 = tr1.getTotalTimeSeconds();
		int s2 = tr2.getTotalTimeSeconds();
		
		return s2-s1;
	}
	
}
