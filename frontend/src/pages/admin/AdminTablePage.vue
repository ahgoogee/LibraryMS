<script setup>
import {reactive, ref} from "vue";
import router from "@/router.js";
import request from "@/request.js";
import {message} from "ant-design-vue";
import DataTableTemplate from "@/components/DataTableTemplate.vue";

const dataSource = ref([])
const total = ref(0)
const pageRequest = reactive({
  page:{
    page_current:0,
    page_size:10,
  },
  sorts:[],
  filters:[]
})
const userColumns = ref([
  {
    title: '用户名',
    dataIndex: 'username',
    key: 'username',
    width:120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],

    canFilter:true,
    editState:false,
    searchContent:'',

    canUpdate:true,
  },
  {
    title: '创建时间',
    dataIndex: 'creation_time',
    key: 'creation_time',
    width:120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],

    canFilter:true,
    editState:false,
    searchContent:'',
  },
  {
    title: '操作',
    key: 'action',
    width:60,
  },
])

const onUpdateTable = async r => {
  let res = await request.post("/list_admin_by_page", r)
  if (res && res.data['is_success']) {
    dataSource.value = res.data.data
  } else {
    dataSource.value = []
  }
}

const onCountUser = async r =>{
  let res = await request.post("/count_admin_by_page", r)
  total.value = res && res.data['is_success'] ? res.data['data'] : 0
}

const onAddUser = () => {
  router.push('/page/admin/add')
}

const onDeleteUser = async row => {
  console.log('user delete',row.id)
  let res = await request.get("/delete_admin_by_id",{id:row.id})
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功删除用户",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "删除失败")
  }
}

const onUpdateUser = async row =>{
  let res = await request.post("/update_admin_by_id",row)
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功更新用户",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "更新失败")
  }
}
</script>

<template>
  <data-table-template
      :columns="userColumns"
      :data-source="dataSource"
      :page-request="pageRequest"
      :total-row="total"
      @on-update-table="onUpdateTable"
      @on-count-entity="onCountUser"
      @on-delete-entity="onDeleteUser"
      @on-update-entity="onUpdateUser"
  >
    <template #header>
      <div>
        <a-button @click="onAddUser">创建管理员</a-button>
      </div>
    </template>
  </data-table-template>
</template>

<style scoped lang="less">
</style>