<template>
  <a-form
      :model="formState"
      name="normal_login"
      class="login-form"
      @finish="onLogin"
      @finishFailed="onLoginFailed"
  >
    <a-form-item
        label="用户"
        name="username"
        :rules="[{ required: true, message: '请输入用户名!' }]"
    >
      <a-input v-model:value="formState.username">
<!--        <template #prefix>-->
<!--          <UserOutlined class="site-form-item-icon" />-->
<!--        </template>-->
      </a-input>
    </a-form-item>

    <a-form-item
        label="密码"
        name="password"
        :rules="[{ required: true, message: '请输入密码!' }]"
    >
      <a-input-password v-model:value="formState.password">
<!--        <template #prefix>-->
<!--          <LockOutlined class="site-form-item-icon" />-->
<!--        </template>-->
      </a-input-password>
    </a-form-item>

    <a-form-item
        label="登录用户"
        name="usertype"
    >
      <a-radio-group v-model:value="formState.usertype">
        <a-radio value="user">用户</a-radio>
        <a-radio value="admin">管理员</a-radio>
      </a-radio-group>
    </a-form-item>

    <a-form-item>
      <a-form-item name="remember" no-style>
        <a-checkbox v-model:checked="formState.remember">记住我</a-checkbox>
      </a-form-item>
<!--      <a class="login-form-forgot" href="">忘记密码?</a>-->
    </a-form-item>

    <a-form-item>
      <a-button :disabled="disabled" type="primary" html-type="submit" class="login-form-button">
        登录
      </a-button>
      或
      <a href="">注册</a>
    </a-form-item>
  </a-form>
</template>
<script setup>
import {reactive, computed, onBeforeMount, inject} from 'vue';
import cache from '@/common/cache.js'
import router from '@/router.js'
import request from "@/request.js";

const formState = reactive({
  username: '',
  password: '',
  usertype: 'user',
  remember: true
});
const onLogin = async values => {
  console.log('Submit:', values);
  //如果选择了remember,那么token的存储时间为永久
  await request.post("/login",{
    "username":formState.username,
    "password":formState.password,
    "usertype":formState.usertype
  }).then(res=>{
    console.log(`res:${res}`)
  })


};
const onLoginFailed = errorInfo => {
  console.log('Failed:', errorInfo);
};

const onRegister = ()=>{

}
const onForgotPassword = ()=>{

}
onBeforeMount(()=>{
  // let usertype = cache.getCache("userType")
  // let token = cache.getCache("Token")
  // if(usertype&&token){
  //   //用户已登录
  //
  //   router.push("/hello")
  // }
})


const disabled = computed(() => {
  return !(formState.username && formState.password && formState.usertype);
});
</script>
<style scoped lang="less">
.login-form{
  border: solid 2px red;
}
</style>