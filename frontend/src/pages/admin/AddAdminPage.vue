<script setup>
import {reactive} from "vue";
import FormInput from "@/components/FormInput.vue";
import request from "@/request.js";
import router from "@/router.js";
import {message} from "ant-design-vue";

const userInfo = reactive({
  username:''
})

const userColumns = [
  {
    label:'用户名',
    type: 'string',
    dataIndex: 'username',
    key: 'username',
    required: true
  }
]

const onAddUser = async user =>{
  let res = await request.post("/add_admin",user)
  if(res&&res.data['is_success']){
    message.info("创建成功")
    await router.push("/page/admin")
  } else
  {
    message.error("创建失败")
  }
}

const onCancel = () =>{
  router.back()
}


</script>

<template>
  <FormInput
      :form-data="userInfo"
      :columns="userColumns"
      @on-submit="onAddUser"
      @on-cancel="onCancel"
  />
</template>

<style scoped lang="less">
</style>