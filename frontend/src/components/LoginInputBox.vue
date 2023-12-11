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
        name="userType"
    >
      <a-radio-group v-model:value="formState.userType">
        <a-radio value="user">用户</a-radio>
        <a-radio value="admin">管理员</a-radio>
      </a-radio-group>
    </a-form-item>

    <a-form-item>
      <a-form-item name="remember" no-style>
        <a-checkbox v-model:checked="formState.remember">记住我</a-checkbox>
      </a-form-item>
      <a class="login-form-forgot" href="">忘记密码?</a>
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

const formState = reactive({
  username: '',
  password: '',
  userType: 'user',
  remember: true
});
const onLogin = values => {
  console.log('Success:', values);
  //如果选择了remember,那么token的存储时间为永久



};
const onLoginFailed = errorInfo => {
  console.log('Failed:', errorInfo);
};

const onRegister = ()=>{

}
const onForgotPassword = ()=>{

}
onBeforeMount(()=>{
  // const $cookies = inject('$cookies');
  // let test = $cookies.get("test")
  // let userType = this.$cookies.get("UserType")
  // let token = this.$cookies.get("Token")
  // if(userType&&token){
  //   //用户已登录
  //
  //   this.router.push("/hello")
  // }
  // this.router.push("/hello")
})


const disabled = computed(() => {
  return !(formState.username && formState.password && formState.userType);
});
</script>
<style scoped lang="less">

</style>