<script setup>
import {reactive} from "vue";

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
  <div class="aup-body-box ">
    <a-form class="flex align-center column" :model="userInfo">
      <a-form-item v-for="column in userColumns" :key="column.key" :required="column.required" :label="column.label">
        <template v-if="column.type === 'string'">
          <a-input :value="column.dataIndex ? userInfo['dataIndex'] : {} " />
        </template>
        <template v-else-if="column.type === 'text'">
          <a-textarea :value="column.dataIndex ? userInfo['dataIndex'] : {} " :rows="4" />
        </template>
        <template v-else-if="column.type === 'number'">
          <a-input-number :value="column.dataIndex ? userInfo['dataIndex'] : {} " />
        </template>
        <template v-else-if="column.type === 'bool'">
          <a-switch :checked="column.dataIndex ? userInfo['dataIndex'] : {} " />
        </template>
      </a-form-item>
      <div class="flex">
        <a-button type="primary">提交</a-button>
        <a-button type="dashed" style="background-color: red;color: white">取消</a-button>
      </div>

    </a-form>


  </div>

</template>

<style scoped lang="less">
.aup-body-box{
  border: solid 2px purple;
  padding: 30px 80px 0;

}
</style>