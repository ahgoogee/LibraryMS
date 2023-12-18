<script setup>
import {onBeforeMount, onMounted, ref,reactive,watch} from "vue";
import router from "@/router.js";
import {CheckOutlined,EditOutlined} from "@ant-design/icons-vue";
import request from "@/request.js";
import {message} from "ant-design-vue";

const updateState = ref(false)
const updatingRecord = reactive({})

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

    canSort:false,
    canFilter:false
  },
])

const userList = ref([])

const pageRequest = reactive({
  page:{
    page_current:0,
    page_size:10,
  },
  sorts:[],
  filters:[]
})

const onUpdateTable = async r => {
  let res = await request.post("/list_user_by_page", r)
  if (res && res.data['is_success']) {
    userList.value = res.data.data
  } else {
    userList.value = []
  }
}

const onSaveFilter = (column,searchContent)=>{
  let target = pageRequest.filters.find(obj=>obj['column']===column)
  if(target){
    target.search_content = searchContent
  }
  else {
    pageRequest.filters.push({column,search_content:searchContent})
  }
}
const onSaveSort = (column,sortDirection)=>{
  let target = pageRequest.sorts.find(obj=>obj['column']===column)
  if(target){
    target.is_asc = sortDirection === 'ascend'
  }
  else {
    pageRequest.sorts.push({column,is_asc:sortDirection === 'ascend'})
  }
}

const onSearchChange = (column)=>{
  // console.log("column",column.key)
  // console.log("content",column.searchContent)
  //接受搜索
  if(column.canFilter){
    onSaveFilter(column.key,column.searchContent)
    column.editState = false
  }
}
const onTableChange = (pagination, filters, sorter)=>{
  //接受排序和分页

  let {current,pageSize} = pagination
  pageRequest.page.page_current = current - 1
  pageRequest.page.page_size = pageSize

  if(sorter.column.canSort){
    let {columnKey,order} = sorter
    console.log('c', columnKey)
    console.log('o', order)
    onSaveSort(columnKey,order)
  }
}

onMounted( async ()=>{await onUpdateTable(pageRequest)})

watch(pageRequest ,onUpdateTable)

const onAddUser = () => {
  router.push('/page/user/add')
}

const onDeleteUser = async row => {
  console.log('user delete',row.id)
  let res = await request.get("/delete_user_by_id",{id:row.id})
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功删除用户",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "删除失败")
  }
}

const onUpdateUser = async row =>{
  let res = await request.post("/update_user_by_id",row)
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功更新用户",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "更新失败")
  }
}

const onEditRecord = (record)=>{
  updatingRecord.value = record
  updateState.value = true
}
const onSubmitEditRecord = async (record)=>{
  if(JSON.stringify(record)!==JSON.stringify(updatingRecord.value))
    await onUpdateUser(updatingRecord.value)

  updatingRecord.value = {}
  updateState.value = false
}


</script>

<template>
  <div class="t-table-box">
    <div>
      <a-button @click="onAddUser">创建用户</a-button>
    </div>
    <a-table :dataSource="userList" :columns="userColumns" @change="onTableChange" >
      <template #headerCell="{ column }">
        <div class="flex space-between align-center">
          <div>{{column.title}}</div>
          <template v-if="column.canFilter">
            <div v-if="column.editState" class="flex align-center">
              <a-input v-model:value="column.searchContent" @pressEnter="onSearchChange(column)" />
              <check-outlined  @click="onSearchChange(column)" />
            </div>
            <div v-else class="flex align-center">
              <div>{{column.searchContent}}</div>
              <edit-outlined @click="column.editState=true" />
            </div>
          </template>
        </div>
      </template>


      <template #bodyCell="{ column, record }">
        <template v-if="column.key==='action'" class="flex column">
          <template v-if="updateState && record.id === updatingRecord.value.id">
            <div @click="onSubmitEditRecord(record)" style="color: #09b6fe;cursor: pointer;">确认</div>
          </template>
          <template v-else>
            <div @click="onEditRecord(record)" style="color: #09b6fe;cursor: pointer;">更新</div>
          </template>

          <div @click="onDeleteUser(record)" style="color: #09b6fe;cursor: pointer;">删除</div>
        </template>
        <template v-else-if="column.canUpdate">
          <div v-if="updateState && record.id === updatingRecord.value.id" >
            <a-input v-model:value="updatingRecord.value[column.dataIndex]" />
          </div>
          <div v-else>
            {{record[column.dataIndex]}}
          </div>
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