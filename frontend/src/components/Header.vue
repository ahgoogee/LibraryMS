<script setup>
import {ReadOutlined} from "@ant-design/icons-vue";
import {reactive} from "vue";

const userInfo = reactive({
  username: 'ahgoogee',
  usertype: 'user',

})

const logout = ()=>{
  console.log("logout")
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
          <p>userinfo</p>
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