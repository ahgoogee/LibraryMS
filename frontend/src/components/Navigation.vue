<script setup>


import {h, ref} from "vue";
import {AppstoreOutlined, MailOutlined} from "@ant-design/icons-vue";

const searchContent = ref("")
const current = ref(['book'])
const items = ref([
  {
    key: 'user',
    icon: () => h(MailOutlined),
    label: '用户管理',
    title: '用户管理',
  },
  {
    key: 'book',
    icon: () => h(AppstoreOutlined),
    label: '图书管理',
    title: '图书管理',
  },
  {
    key: 'type',
    icon: () => h(AppstoreOutlined),
    label: '分类管理',
    title: '分类管理',
  },
  {
    key: 'record',
    icon: () => h(AppstoreOutlined),
    label: '借阅管理',
    title: '借阅管理',
  },
])


const onSearch= ()=>{

}

</script>

<template>
  <div class="n-navigation-box flex">
    <a-input-search
        v-model:value="searchContent"
        placeholder="input search text"
        style="width: 200px"
        @search="onSearch"
    />
    <a-menu v-model:selectedKeys="current" mode="horizontal" :items="items" />
  </div>
</template>

<style scoped>
.n-navigation-box{
  padding-left: 50px;
  height: 50px;
  width: 100vw;
  border: solid 2px #09b6fe;

  font-size: 24px;
  line-height: 42px;

}
</style>