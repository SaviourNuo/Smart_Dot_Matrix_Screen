<template>
	<view class="content">
			<view class="text-box" scroll-y="true">
				<text>LCD屏幕控制台</text>
			</view>
			<view class="uni-list">
				<view class="uni-list-cell uni-list-cell-pd">
					<view class="uni-list-cell-db">开关1</view>
					<switch @change="switch1Change" />
				</view>
				<view class="uni-list-cell uni-list-cell-pd">
					<view class="uni-list-cell-db">开关2</view>
					<switch @change="switch2Change" />
				</view>
				<view class="uni-list-cell uni-list-cell-pd">
					<view class="uni-list-cell-db">开关3</view>
					<switch @change="switch3Change" />
				</view>
			</view>
			<view class="uni-list">
				<view class="uni-list-cell uni-list-cell-pd">
					<input class="uni-input" v-model="myText" type="text" placeholder="支持英文与部分中文字符" />
				</view>
			</view>
			<button type="default" @click="generateText" style='margin-top: 30rpx;'> 数据发送 </button>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				myText: "",
				switch1: false,
				switch2: false,
				switch3: false,
			}
		},
		onLoad() {

		},
		methods: {
			switch1Change: function (e) {
				console.log('switch1 发生 change 事件，携带值为', e.target.value)
				this.switch1 = e.target.value;
				
			},
			switch2Change: function (e) {
				console.log('switch2 发生 change 事件，携带值为', e.target.value)
				this.switch2 = e.target.value;
			},
			switch3Change: function (e) {
				console.log('switch3 发生 change 事件，携带值为', e.target.value)
				this.switch3 = e.target.value;
			},
			generateText: function(){
				let that = this;
				uni.openBluetoothAdapter({
				  success: function (res) {
					uni.showToast({
						icon: "loading",
						title: '正在搜索设备'
					})
					//开始搜索硬件设备
					uni.startBluetoothDevicesDiscovery({
					  // services: ["20:DF:26:A8:CB:76"],
					  allowDuplicatesKey: false,
					  success(e) {
						console.log('开始搜索蓝牙设备:' + e.errMsg);
					  }
					})
					uni.onBluetoothDeviceFound(devices => {
						// console.log(devices.devices)
						if(devices.devices[0].deviceId === "B4:10:7B:C4:76:B3"){
							console.log('发现设备');
							let deviceId = "B4:10:7B:C4:76:B3";
							uni.showToast({
								title: '正在连接蓝牙...',
								icon: 'loading',
								duration: 9000
							});
							//连接蓝牙
							uni.createBLEConnection({
								deviceId,
								success: res => {
									console.log(res);
									console.log('连接蓝牙成功:' + res.errMsg);
									// 连接设备后断开搜索 并且不能搜索设备
									uni.stopBluetoothDevicesDiscovery();
									uni.hideToast();
									uni.showToast({
										title: '连接成功',
										icon: 'success',
										duration: 2000
									});
									function sleep (time) {
									  return new Promise((resolve) => setTimeout(resolve, time));
									}
									sleep(1000).then(async () => {
										uni.showToast({
											title: '正在进行数据传输...',
											icon: 'loading',
											duration: 5000
										});
										let serviceId = "0000FFE0-0000-1000-8000-00805F9B34FB";
										let characteristicId = "0000FFE1-0000-1000-8000-00805F9B34FB";
										// var bf = Uint8Array.from(new Uint8Array(64).keys())
										let textStr="华中科技大学电子信息》与通》信学院徐诺曹中烨 "
										let textIndex = []
										let ctr = 0
										if((!that.switch1)&&(!that.switch2)&&(!that.switch3)) {
											ctr+=0xF0;
										}//000
										else if((!that.switch1)&&(!that.switch2)&&(that.switch3)) {
											ctr+=0xF1;
										}//001
										else if((!that.switch1)&&(that.switch2)&&(!that.switch3)) {
											ctr+=0xF2;
										}//010
										else if((!that.switch1)&&(that.switch2)&&(that.switch3)) {
											ctr+=0xF3;
										}//011
										else {
											ctr+=0xF4;
										}//100 101 110 111
										textIndex.push(ctr)
										for(let i = 0; i < that.myText.length; ++i){
											textIndex.push(textStr.indexOf(that.myText[i]))
										}
										textIndex.push(0x0D)
										textIndex.push(0x0A)
										console.log(textIndex)
										var bf = Uint8Array.from(new Uint8Array(textIndex));
										// bf.push(Uint8(0x0D))
										// bf.push(Uint8(0x0A))
										console.log(bf);
										let i = 0;
										while(i + 20 <= bf.length){
											var tempBf = bf.slice(i, i+20);
											await uni.writeBLECharacteristicValue({
											  deviceId,
											  serviceId,
											  characteristicId,
											  value: tempBf
											})
											i = i + 20;
										}
										if(i < bf.length){
											var tempBf = bf.slice(i);
											await uni.writeBLECharacteristicValue({
											  deviceId,
											  serviceId,
											  characteristicId,
											  value: tempBf
											})
										}
										uni.showToast({
											title: '数据传输成功',
											icon: 'success',
											duration: 2000
										});
										uni.closeBLEConnection({
										  deviceId,
										  success(res) {
											console.log('蓝牙已断开')
										  }
										})
									})
								},
								fail: e => {
									console.log('连接蓝牙失败，错误码：' + e.errCode);
									uni.hideToast();
									uni.showToast({
										title: '连接失败，请重试',
										icon: 'none',
										duration: 2000
									});
								}
							});
						}
					})
				  },
				  fail: function (e) {
					uni.showToast({
						icon: "none",
						title: '初始化蓝牙失败，错误码：' + (e.errCode + '\n' + e.errMsg),
						duration: 2000
					})
				  },
				  
				})
			}
		}
	}
</script>

<style>
	.uni-list {
		background-color: #FFFFFF;
		position: relative;
		width: 100%;
		display: flex;
		flex-direction: column;
		margin-top: 20rpx;
		margin-bottom: 40rpx;
	}
	.uni-list-cell {
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		align-items: center;
	}
	.uni-list-cell-pd {
		padding: 22rpx 30rpx;
	}
	.text-box {
		margin-bottom: 40rpx;
		margin-top: 20rpx;
		padding: 40rpx;
		display: flex;
		min-height: 30rpx;
		background-color: #FFFFFF;
		justify-content: center;
		align-items: center;
		text-align: center;
		font-size: 30rpx;
		color: #353535;
		line-height: 1.8;
	}
	.uni-input {
		height: 50rpx;
		padding: 15rpx 25rpx;
		line-height:50rpx;
		width: 80%;
		font-size:28rpx;
		background:#d3d3d3;
		flex: 1;
	}
	.content {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
	}

	.logo {
		height: 200rpx;
		width: 200rpx;
		margin-top: 200rpx;
		margin-left: auto;
		margin-right: auto;
		margin-bottom: 50rpx;
	}

	.text-area {
		display: flex;
		justify-content: center;
	}

	.title {
		font-size: 36rpx;
		color: #8f8f94;
	}
</style>
