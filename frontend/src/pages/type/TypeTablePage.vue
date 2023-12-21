<script setup>
import {reactive, ref} from "vue";
import request from "@/request.js";
import router from "@/router.js";
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

const columns = ref([
  {
    title: '类型名',
    dataIndex: 'name',
    key: 'name',
    width: 120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],

    canFilter:true,
    editState:false,
    searchContent:'',

    canUpdate:true,
  },
  {
    title: '级别',
    dataIndex: 'level',
    key: 'level',
    width: 120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],

    canFilter:true,
    editState:false,
    searchContent:'',
  },
  {
    title: '父类别',
    dataIndex: 'parent_name',
    key: 'parent_id',
    width: 120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],
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

const getParentName = async id=>{
  let type = await request.get("/get_type_by_id",{id})
  return  type && type.data['is_success']
      ? type.data['data']['name']
      : ""
}

const onUpdateTable = async r=>{
  let res = await request.post("/list_type_by_page", r)
  if (res && res.data['is_success']) {
    dataSource.value = await Promise.all(res.data.data.map(async row=>{
      let parent_name = row.level===1?await getParentName(row['parent_id']):"";
      return {
        parent_name,
        ...row
      }
    }));
  } else {
    dataSource.value = []
  }
}

const onCountType = async r =>{
  let res = await request.post("/count_type_by_page", r)
  total.value = res && res.data['is_success'] ? res.data['data'] : 0
}

const onAddType = () => {
  router.push('/page/type/add')
}

const onDeleteType = async row => {
  let res = await request.get("/delete_type_by_id",{id:row.id})
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功删除用户",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "删除失败")
  }
}

const onUpdateType = async row =>{
  let res = await request.post("/update_type_by_id",row)
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功更新图书类别",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "更新失败")
  }
}

</script>

<template>
  <data-table-template
      :columns="columns"
      :data-source="dataSource"
      :page-request="pageRequest"
      :total-row="total"
      @on-update-table="onUpdateTable"
      @on-count-entity="onCountType"
      @on-delete-entity="onDeleteType"
      @on-update-entity="onUpdateType"
  >
    <template #header>
      <div>
        <a-button @click="onAddType">创建类别</a-button>
      </div>
    </template>
  </data-table-template>
</template>

<style scoped lang="less">

</style>