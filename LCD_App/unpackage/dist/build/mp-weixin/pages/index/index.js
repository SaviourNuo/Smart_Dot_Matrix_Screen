(global["webpackJsonp"]=global["webpackJsonp"]||[]).push([["pages/index/index"],{"0952":function(e,t,n){"use strict";(function(e){n("70fa");o(n("66fd"));var t=o(n("1ca5"));function o(e){return e&&e.__esModule?e:{default:e}}wx.__webpack_require_UNI_MP_PLUGIN__=n,e(t.default)}).call(this,n("543d")["createPage"])},"1ca5":function(e,t,n){"use strict";n.r(t);var o=n("54ee"),c=n("a6cb");for(var i in c)"default"!==i&&function(e){n.d(t,e,(function(){return c[e]}))}(i);n("c1a4");var r,a=n("f0c5"),u=Object(a["a"])(c["default"],o["b"],o["c"],!1,null,null,null,!1,o["a"],r);t["default"]=u.exports},"203e":function(e,t,n){},"54ee":function(e,t,n){"use strict";var o;n.d(t,"b",(function(){return c})),n.d(t,"c",(function(){return i})),n.d(t,"a",(function(){return o}));var c=function(){var e=this,t=e.$createElement;e._self._c},i=[]},a6cb:function(e,t,n){"use strict";n.r(t);var o=n("f3f5"),c=n.n(o);for(var i in o)"default"!==i&&function(e){n.d(t,e,(function(){return o[e]}))}(i);t["default"]=c.a},c1a4:function(e,t,n){"use strict";var o=n("203e"),c=n.n(o);c.a},f3f5:function(e,t,n){"use strict";(function(e){Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0;var o=c(n("a34a"));function c(e){return e&&e.__esModule?e:{default:e}}function i(e,t,n,o,c,i,r){try{var a=e[i](r),u=a.value}catch(s){return void n(s)}a.done?t(u):Promise.resolve(u).then(o,c)}function r(e){return function(){var t=this,n=arguments;return new Promise((function(o,c){var r=e.apply(t,n);function a(e){i(r,o,c,a,u,"next",e)}function u(e){i(r,o,c,a,u,"throw",e)}a(void 0)}))}}var a={data:function(){return{myText:"",myText2:"",leftSwitch:!1,rowSwitch:!1}},onLoad:function(){},methods:{switch1Change:function(e){console.log("switch1 发生 change 事件，携带值为",e.target.value),this.leftSwitch=e.target.value},switch2Change:function(e){console.log("switch2 发生 change 事件，携带值为",e.target.value),this.rowSwitch=e.target.value},generateText:function(){var t=this;e.openBluetoothAdapter({success:function(n){e.showToast({icon:"loading",title:"正在搜索设备"}),e.startBluetoothDevicesDiscovery({allowDuplicatesKey:!1,success:function(e){console.log("开始搜索蓝牙设备:"+e.errMsg)}}),e.onBluetoothDeviceFound((function(n){if("B4;10;7B;C4;76;B3"===n.devices[0].deviceId){console.log("发现设备");var c="B4;10;7B;C4;76;B3";e.showToast({title:"正在连接蓝牙...",icon:"loading",duration:9e3}),e.createBLEConnection({deviceId:c,success:function(n){function i(e){return new Promise((function(t){return setTimeout(t,e)}))}console.log(n),console.log("连接蓝牙成功:"+n.errMsg),e.stopBluetoothDevicesDiscovery(),e.hideToast(),e.showToast({title:"连接成功",icon:"success",duration:2e3}),i(1e3).then(r(o.default.mark((function n(){var i,r,a,u,s,l,f,d,h,v,g,w,x;return o.default.wrap((function(n){while(1)switch(n.prev=n.next){case 0:if(e.showToast({title:"正在进行数据传输...",icon:"loading",duration:5e3}),i="0000FFE0-0000-1000-8000-00805F9B34FB",r="0000FFE1-0000-1000-8000-00805F9B34FB",a=" 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,!.张晓雪、周嘉文，电子信息与通信学院。",u=[],s=0,t.leftSwitch||(s+=240),t.rowSwitch&&(s+=15),u.push(s),t.rowSwitch)for(f=Math.max(t.myText.length,t.myText2.length),d=(f-t.myText.length)/2,h=(f-t.myText2.length)/2,v=0;v<f;++v)v<d||v-d>=t.myText.length?u.push(0):u.push(a.indexOf(t.myText[v-d])),v<h||v-h>=t.myText2.length?u.push(0):u.push(a.indexOf(t.myText2[v-h]));else for(l=0;l<t.myText.length;++l)u.push(a.indexOf(t.myText[l]));u.push(13),u.push(10),console.log(u),g=Uint8Array.from(new Uint8Array(u)),console.log(g),w=0;case 16:if(!(w+20<=g.length)){n.next=23;break}return x=g.slice(w,w+20),n.next=20,e.writeBLECharacteristicValue({deviceId:c,serviceId:i,characteristicId:r,value:x});case 20:w+=20,n.next=16;break;case 23:if(!(w<g.length)){n.next=27;break}return x=g.slice(w),n.next=27,e.writeBLECharacteristicValue({deviceId:c,serviceId:i,characteristicId:r,value:x});case 27:e.showToast({title:"数据传输成功",icon:"success",duration:2e3}),e.closeBLEConnection({deviceId:c,success:function(e){console.log("蓝牙已断开")}});case 29:case"end":return n.stop()}}),n)}))))},fail:function(t){console.log("连接蓝牙失败，错误码："+t.errCode),e.hideToast(),e.showToast({title:"连接失败，请重试",icon:"none",duration:2e3})}})}}))},fail:function(t){e.showToast({icon:"none",title:"初始化蓝牙失败，错误码："+t.errCode+"\n"+t.errMsg,duration:2e3})}})}}};t.default=a}).call(this,n("543d")["default"])}},[["0952","common/runtime","common/vendor"]]]);