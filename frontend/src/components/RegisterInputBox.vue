<script setup>
import {reactive} from "vue";
import {message} from "ant-design-vue";
import request from "@/request.js";
import router from "@/router.js";
import cache from "@/common/cache.js";

const form = reactive({
  username:'',
  password:'',
  retry:'',
})

const onRegister = async (values)=>{
  message.info(JSON.stringify(values))
  let res = await request.post("/register",{
    username:values.username,
    password:values.password
  })
  if(res && res.data['is_success']){
    message.info("注册成功")
    cache.setCache("Token","")
    cache.setCache("username","")
    cache.setCache("usertype","")
    await router.push("/login")
  }
}
</script>

<template>
  <div>
    <h1 style="padding: 15px">注册</h1>
    <a-form
        :model="form"
        name="normal_register"
        @finish="onRegister"
        @finishFailed=""
        class="rib-box"
    >
      <a-form-item
          label="用 户"
          name="username"
          :rules="[{ required: true, message: '请输入用户名!' }]"
      >
        <a-input v-model:value="form.username"/>
      </a-form-item>

      <a-form-item
          label="密 码"
          name="password"
          :rules="[{ required: true, message: '请输入密码!' }]"
      >
        <a-input-password v-model:value="form.password"/>
      </a-form-item>

      <a-form-item
          label="重输密码"
          name="retry"
          :rules="[{ required: true, message: '请重新输入密码!' }]"
      >
        <a-input-password v-model:value="form.retry"/>
      </a-form-item>

      <a-form-item class="flex">
        <a-button :disabled="!(form.username&&form.password&&form.retry&&form.password===form.retry)" type="primary" html-type="submit" class="login-form-button">
          注册
        </a-button>
        或
        <router-link to="/login">登录</router-link>
      </a-form-item>

    </a-form>
  </div>

</template>

<style scoped lang="less">
.rib-box{
  display: flex;
  flex-direction: column;
  align-items: center;
  border: solid 1px #8c8c8c;
  padding: 20px;
  border-radius: 15px;
}
</style>