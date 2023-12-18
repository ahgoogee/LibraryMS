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
  let res = await request.post("/add_user",user)
  if(res&&res.data['is_success']){
    message.info("创建成功")
    await router.push("/page/user")
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
  <div class="fi-body-box ">
    <FormInput :form-data="userInfo" :columns="userColumns">
      <template #footer>
        <div class="flex">
          <a-button type="primary" @click="onAddUser(userInfo)">提交</a-button>
          <a-button type="dashed" style="background-color: red;color: white" @click="onCancel">取消</a-button>
        </div>
      </template>
    </FormInput>

  </div>

</template>

<style scoped lang="less">
.fi-body-box{
  border: solid 2px purple;
  padding: 30px 80px 0;

}
</style>