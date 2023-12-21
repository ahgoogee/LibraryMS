<script setup>
import {ReadOutlined} from "@ant-design/icons-vue";
import {onMounted, reactive} from "vue";
import cache from "@/common/cache.js";
import router from "@/router.js";
import request from "@/request.js";

const userInfo = reactive({
  username: '',
  usertype: '',
})

onMounted( async ()=>{
  userInfo.username = cache.getCache("username")
  userInfo.usertype = cache.getCache("usertype")
  if(userInfo.usertype === 'user'){
    let res = await request.get("/get_user_by_username",{username:userInfo.username})
    if(res && res.data['is_success']){
      cache.setCache("user_id",res.data['data']['id'])
    }
  }

})


const logout = ()=>{
  cache.setCache("Token","")
  cache.setCache("username","")
  cache.setCache("usertype","")
  router.push("/login").then()
}
</script>

<template>
  <div class="h-header-box flex space-between">
    <!--Logo区域-->
    <div class="h-logo-box flex space-around align-center">
      <ReadOutlined/>
      <div class="h-line" ></div>
      <h1>Library</h1>
    </div>

    <!--用户信息区-->
    <div class="h-userinfo-box flex space-around align-center">
      <div style="margin-right: 20px">{{userInfo.usertype}}</div>
      <a-popover :title="userInfo.username" placement="bottomLeft">
        <template #content>
          <a-button type="primary" @click="logout">注销</a-button>
        </template>
        <ReadOutlined/>
      </a-popover>
    </div>


  </div>
</template>

<style scoped lang="less">
.h-header-box{
  height: 50px;
  width: 100vw;
  border: solid 2px red;

  .h-logo-box{
    margin-left: 40px;


    .h-line{
      margin: 0 20px 0;
      height: 40px;
      width: 3px;
      background-color: #00ab42;
    }
  }

  .h-userinfo-box{
    margin-right: 50px;


  }
}
</style>