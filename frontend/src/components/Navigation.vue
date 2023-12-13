<script setup>
import {h, ref} from "vue";
import {AppstoreOutlined, MailOutlined} from "@ant-design/icons-vue";
import router from "@/router.js"

const searchContent = ref("")
const current = ref(['book'])
const items = ref([
  {
    key: 'user',
    icon: () => h(MailOutlined),
    label: '用户管理',
    title: '用户管理',
    path: '/user'
  },
  {
    key: 'book',
    icon: () => h(AppstoreOutlined),
    label: '图书管理',
    title: '图书管理',
    path: '/book'
  },
  {
    key: 'type',
    icon: () => h(AppstoreOutlined),
    label: '分类管理',
    title: '分类管理',
    path: '/type'
  },
  {
    key: 'record',
    icon: () => h(AppstoreOutlined),
    label: '借阅管理',
    title: '借阅管理',
    path: '/record'
  },
])


const onSearch= ()=>{

}
const onChange= ({item,key,keyPath})=>{
  let target = "/page" + item.path
  console.log(target)
  router.push(target)
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
    <a-menu v-model:selectedKeys="current" mode="horizontal" :items="items" @click="onChange" />
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