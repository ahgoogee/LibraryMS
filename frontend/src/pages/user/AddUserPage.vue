<script setup>
import {reactive} from "vue";
import FormInput from "@/components/FormInput.vue";

const userInfo = reactive({
  username:'',
  age:0
})

const userColumns = [
  {
    label:'用户名',
    type: 'string',
    dataIndex: 'username',
    key: 'username',
    required: true
  },
  {
    label:'年龄',
    type: 'number',
    dataIndex: 'age',
    key: 'age',
    required: false
  }
]

</script>

<template>
  <div class="fi-body-box ">
    <FormInput :form-data="userInfo" :columns="userColumns">
      <template #footer>
        <div class="flex">
          <a-button type="primary">提交</a-button>
          <a-button type="dashed" style="background-color: red;color: white">取消</a-button>
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