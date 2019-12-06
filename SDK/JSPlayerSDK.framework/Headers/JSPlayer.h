//
//  Player.h
//  LiveVideoPlayerSDK
//
//  Created by weijh on 2018/7/18.
//  Copyright © 2018年 juns. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVKit/AVKit.h>
#import <UIKit/UIKit.h>

#define PREFIX(x) JS##x

@class PREFIX(VideoPlayer);

#pragma mark - VideoPlayerSkinDelegate

/**
 ui 皮肤需要实现的接口
 */
@protocol PREFIX(VideoPlayerSkinDelegate) <NSObject>

/**
 关联的播放器
 */
@property(nonatomic, weak) PREFIX(VideoPlayer)* player;
/**
 封面图
 */
@property(nonatomic, retain) UIImage* poster;
@property(nonatomic) NSString* tip;
@property(nonatomic) BOOL isVip;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
    mute:(BOOL)isMute;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
    stateDidChange:(int)state;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
    currentTimeDidChange:(double)time duration:(double)duration;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
    bufferTimeDidChange:(double)time;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
    displayModeDidChange:(int)mode;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
    controllerDisplayModeDidChange:(int)mode;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
showDialog:(NSString*)title btn:(NSString*)btn showBackground:(BOOL)showBackground showLoading:(BOOL)showLoading btnClick:(void(^)(void))btnClick;

-(void)PREFIX(VideoPlayer):(PREFIX(VideoPlayer)*)player
hideDialog:(BOOL)_;

@end

#pragma mark - VideoPlayer

/**
 对AVPlayer进行的封装，会加载LiveVideoPlayerSDKUI.bundle作为皮肤
 */
@interface PREFIX(VideoPlayer) : UIView

@property(nonatomic)BOOL modeMultiplayer;

@property(nonatomic)BOOL modePortrait;

@property(nonatomic,retain,readonly) AVPlayer* avplayer;
/**
 皮肤的根对象
 */
@property(nonatomic,retain) UIView<PREFIX(VideoPlayerSkinDelegate)>* controlView;
/**
 在播放器最上层可以嵌入其他ui控件
 */
@property(retain) UIView* overlayView;
/**
 封面图
 */
@property(nonatomic,retain) UIImage* poster;
@property(nonatomic) NSString* tip;

/**
 是否自动播放(默认开启)
 */
@property BOOL autoplay;
@property double lastPosition;

@end


typedef enum PREFIX(PlayerState) {
    PREFIX(PlayerStateUnknown) = 1,            // 播放前
    PREFIX(PlayerStateError),              // 出现错误
    PREFIX(PlayerStateReadyToPlay),        // 可以播放
    PREFIX(PlayerStateBuffering),          // 缓冲中
    PREFIX(PlayerStateBufferFinish),     // 缓冲完毕
    PREFIX(PlayerStatePlaying),            // 播放
    PREFIX(PlayerStatePause),              // 播放暂停
    PREFIX(PlayerStateStopped)             // 播放结束
} PREFIX(PlayerState);

@interface PREFIX(VideoPlayer)(Playing)

/**
 当前视频播放到的时间点
 */
@property(nonatomic) double currentTime;
/**
 当前播放的视频的长度，若为直播或者获取不到长度则为0
 */
@property(nonatomic,readonly) double duration;
/**
 当前播放器的状态
 */
@property(nonatomic,readonly) PREFIX(PlayerState) state;
/**
 是否静音
 */
@property(nonatomic) BOOL mute;
/**
 当前播放视频的url地址
 */
@property(nonatomic,readonly) NSString* url;
/**
 是否收费视频(默认关闭)
 */
@property(nonatomic) BOOL isVip;

/**
 加载指定url的视频

 @param url 视频地址
 */
-(void)load:(NSString*)url;

/**
 开始播放视频，如果当前视频为暂停状态，则恢复播放
 */
-(void)play;

-(void)playFromTime:(double)time;

-(void)playFromTime:(double)time toTime:(double)toTime;

-(void)playFromTime:(double)time url:(NSString*)url;

/**
 加载制定url视频并开始播放

 @param url 视频地址
 */
-(void)play:(NSString*)url;

/**
 播放器当前是否为可播放状态

 @return 是否可播放
 */
-(BOOL)canPlay;
-(void)needUpdateState;

-(void)pause;
-(void)stop;


@end

@interface PREFIX(VideoPlayer)(Fullscreen)

@property(nonatomic) BOOL fullscreen;

@end


@interface PREFIX(VideoPlayer)(Dialog)

/**
 在播放器顶层显示一个对话框

 @param title 对话框文本
 @param btnTitle 对话框按钮文本，如果为空则不显示按钮
 @param showBackground 对话框是否显示全黑色背景，遮挡住下面的其他播放器内容
 @param showLoading 对话框是否显示一个loading控件
 @param onBtnClick 对话框按钮点击事件
 */
-(void)showDialog:(NSString*)title btnTitle:(NSString*)btnTitle showBackground:(BOOL)showBackground showLoading:(BOOL)showLoading onBtnClick:(void(^)(void))onBtnClick;

-(void)hideDialog;

@end

@interface PREFIX(VideoPlayer)(Control)

/**
 显示或隐藏播放器操作控件

 @param show 显示/隐藏
 */
-(void)showControl:(BOOL)show;

@end

@interface PREFIX(VideoPlayer)(Screenshot)

@property(nonatomic) BOOL isScreenshotMode;

-(UIImage*)screenshot;

@end

#pragma mark - LiveVideoPlayer

typedef NS_ENUM(NSInteger, PREFIX(ReadyStatus)){
    PREFIX(ReadyStatusLiveReady) = 1,
    PREFIX(ReadyStatusVodReady),
    PREFIX(ReadyStatusVodProgress),
    PREFIX(ReadyStatusVodOff)
};

typedef NS_ENUM(NSInteger, PREFIX(PlayerEvent)){
    PREFIX(PlayerEventLiveWillStart) = 1,
    PREFIX(PlayerEventLiveWillStop),
    PREFIX(PlayerEventLiveDidStart),
    PREFIX(PlayerEventLiveDidStop),
    PREFIX(PlayerEventLivePic),
    PREFIX(PlayerEventBeforePlay),
    PREFIX(PlayerEventPlay),
    PREFIX(PlayerEventPause),
    PREFIX(PlayerEventFinished),
    PREFIX(PlayerEventError),
    PREFIX(PlayerEventControlsHide),
    PREFIX(PlayerEventControlsShow),
    PREFIX(PlayerEventReady),
    PREFIX(PlayerEventWillEnterFullscreen),
    PREFIX(PlayerEventDidEnterFullscreen),
    PREFIX(PlayerEventWillExitFullscreen),
    PREFIX(PlayerEventDidExitFullscreen),
    PREFIX(PlayerEventMute),
    PREFIX(PlayerEventUnmute)
};

@protocol PREFIX(PlayerEventCallback)
/**
 播放器事件（包括平台事件，如 livewillstart）

 @param event 事件名
 @param data 事件携带的数据
 @return 暂不使用
 */
-(BOOL)PREFIX(PlayerEvent):(PREFIX(PlayerEvent))event data:(id)data;
@end

@interface PREFIX(LiveVideoPlayer) : PREFIX(VideoPlayer)

/**
 SDK版本

 @return 版本号
 */
+(int)version;

/**
 当前播放的录像id

 @return 录像id
 */
-(long)recordID;

/**
 设置播放器事件回调

 @param callback 回调引用
 */
-(void)setEventCallback:(id<PREFIX(PlayerEventCallback)>)callback;

/**
 获取封面图

 @return 封面图
 */
-(UIImage*)posterImage;

/**
 获取封面图的url

 @return url
 */
-(NSString*)posterImageUrl;

/**
 获取播放器操作控件的引用，可以插入其他UIView

 @return uiview
 */
-(UIView*)getControllerView;

@end


@interface PREFIX(LiveVideoPlayer) (Begin)

/**
 接入平台，获取直播间相关信息

 @param _roomID 直播间Id，传0表示不关联直播间
 @param _apiServer 平台url
 */
-(void)ready:(long)_roomID apiServer:(NSString*)_apiServer;
-(void)ready:(long)_roomID;

/**
 接入平台，获取直播见相关信息，使用多播放器样式，用做列表界面
 @param _roomID 直播间Id，传0表示不关联直播间
 @param _apiServer 平台url
 */
-(void)readyForMultiplayer:(long)_roomID apiServer:(NSString*)_apiServer;

/**
 断开与平台的通讯，回收资源。
 调用后释放所有资料，前后台切换，wifi检测等无法使用。
 */
-(void)end;


@end

//shortcut
typedef PREFIX(LiveVideoPlayer) PREFIX(Player) ;
