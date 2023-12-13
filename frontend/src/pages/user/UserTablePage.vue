<script setup>
import {ref} from "vue";
import router from "@/router.js";


const onUpdateUser = user=>{
  console.log('user update',user)
  router.push('/page/user/add')
}

const userList = ref([
  {
    id: 1,
    username: '张三',
    age: 21,
  },
  {
    id: 2,
    username: '李四',
    age: 20

  },
  {
    id: 3,
    username: '王二',
    age: 22

  }
])
const userColumns = [
  {
    title: '用户名',
    dataIndex: 'username',
    key: 'username'
  },
  {
    title: '年龄',
    dataIndex: 'age',
    key: 'age'
  },
  {
    title: '操作',
    key: 'action',
  },
]
</script>

<template>
  <div class="t-table-box">
    <a-table :dataSource="userList" :columns="userColumns" >
      <template #bodyCell="{ column, record }">
        <template v-if="column.key==='action'">
          <div @click="onUpdateUser(record)" style="color: #09b6fe;cursor: pointer;">修改</div>
        </template>



      </template>
    </a-table>
  </div>
</template>

<style scoped lang="less">
  .t-table-box{
    border: solid 2px red;
  }
</style>