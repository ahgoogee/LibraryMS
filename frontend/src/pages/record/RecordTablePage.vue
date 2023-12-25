<script setup>
import {reactive, ref} from "vue";
import request from "@/request.js";
import {message} from "ant-design-vue";
import DataTableTemplate from "@/components/DataTableTemplate.vue";
import cache from "@/common/cache.js";

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
    title: '借阅人',
    dataIndex: 'user_name',
    key: 'user_id',
    width:120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],
  },
  {
    title: '被借图书',
    dataIndex: 'book_name',
    key: 'book_id',
    width:120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],
  },
  {
    title: '状态',
    dataIndex: 'state',
    key: 'state',
    width:120,
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


const getUserNameMap = async id_list =>{
  let res = await request.post("/list_user_by_id_list", {id_list:id_list})
  let idToNameMap = {}
  if  (res && res.data['is_success']){
    res.data['data'].forEach(user=>{
      idToNameMap[user.id]=user
    })
  }
  return idToNameMap
}

const getBookNameMap = async id_list =>{
  let res = await request.post("/list_book_by_id_list", {id_list:id_list})
  let idToNameMap = {}
  if  (res && res.data['is_success']){
    res.data['data'].forEach(book=>{
      idToNameMap[book.id]=book
    })
  }
  return idToNameMap
}

const onUpdateTable = async r => {
  let tmp_request = JSON.parse(JSON.stringify(r))
  if(cache.isUser()){
    let user_id = cache.getCache("user_id")??0
    tmp_request.filters.push({
      column:'user_id',
      search_content:`${user_id}`
    })

  }

  let res = await request.post("/list_record_by_page", tmp_request)
  if (res && res.data['is_success']) {
    let user_name_map = await getUserNameMap(res.data['data'].map(d=>d['user_id']))
    let book_name_map = await getBookNameMap(res.data['data'].map(d=>d['book_id']))

    console.log(user_name_map)
    console.log(book_name_map)

    dataSource.value = res.data['data'].map(row=>{
      return {
        user_name: user_name_map?.[row['user_id']]?.['username']??`user${row.id}`,
        book_name: book_name_map?.[row['book_id']]?.['name']??`book${row.id}`,
        id:row.id,
        state:row['stop_time']>row['creation_time']?"已归还":"未归还",
        state_bool:row['stop_time']>row['creation_time'],
        creation_time:row.creation_time
      }})
  } else {
    dataSource.value = []
  }
}

const onCountRecord = async r => {
  let res = await request.post("/count_record_by_page", r)
  total.value = res && res.data['is_success'] ? res.data['data'] : 0
}

const onGiveBack = async r => {
  let res = await request.get("/give_back",{
    record_id:r['id']
  })
  if(res && res.data['is_success']){
    message.info("归还成功")
    await onUpdateTable(pageRequest)
  }else {
    message.info("归还失败")
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
      @on-count-entity="onCountRecord"
  >
    <template #action="{ column,record }">
      <a-button
          @click="onGiveBack(record)"
          :disabled="record['state_bool']">
        归还
      </a-button>
    </template>
  </data-table-template>
</template>

<style scoped lang="less">

</style>