<script setup>
import {h, onMounted, ref} from "vue";
import {AppstoreOutlined, MailOutlined} from "@ant-design/icons-vue";
import router from "@/router.js"
import cache from "@/common/cache.js";

const current = ref([router.currentRoute.value.fullPath.match(/(?<=\/page\/)([a-zA-Z]+)+(?=\/[a-zA-Z]+)/g).at(0)])
const items = ref([])

onMounted(()=>{
  if(cache.isAdmin()){
    items.value.push(
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
        {
          key: 'user',
          icon: () => h(MailOutlined),
          label: '用户管理',
          title: '用户管理',
          path: '/user'
        },
        {
          key: 'admin',
          icon: () => h(MailOutlined),
          label: '管理员管理',
          title: '管理员管理',
          path: '/admin'
        },

    )
  }
  else {
    items.value.push(
        {
          key: 'book',
          icon: () => h(AppstoreOutlined),
          label: '图书管理',
          title: '图书管理',
          path: '/book'
        },
        {
          key: 'record',
          icon: () => h(AppstoreOutlined),
          label: '借阅管理',
          title: '借阅管理',
          path: '/record'
        },
    )
  }
})


const onChange= ({item,key,keyPath})=>{
  let target = "/page" + item.path
  console.log(current.value)
  router.push(target)
}

</script>

<template>
  <div class="n-navigation-box flex">
    <a-menu
        v-model:selectedKeys="current"
        mode="horizontal"
        :items="items"
        @click="onChange" />
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