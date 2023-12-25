<script setup>
import {reactive, ref} from "vue";
import request from "@/request.js";
import router from "@/router.js";
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
    title: '图书名',
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
    title: '描述',
    dataIndex: 'description',
    key: 'description',
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
    title: '类别',
    dataIndex: 'typename',
    key: 'type_id',
    width: 120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],
  },
  {
    title: '状态',
    dataIndex: 'borrow_state',
    key: 'borrow_state',
    width: 120,

    canSort:true,
    sorter: true,
    sortDirections: ['descend','ascend'],

    canFilter:true,
    editState:false,
    searchContent:'',
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



const getBookTypeNameMap = async (id_list)=>{
  let res = await request.post("/list_type_by_id_list",{id_list:id_list})
  let idToTypeNameMap = {}
  let oneLevelParentIdList = [] //二级类别,需要搜索一级类别,即level==0的type
  let onLevelType = []
  if(res && res.data['is_success']){
    res.data['data'].forEach(type=>{
      if(type['level']===1){
        oneLevelParentIdList.push(type['parent_id'])
        onLevelType.push(type)
      }
      else {
        idToTypeNameMap[type['id']] = type
      }
    })
    //所有的0级类别就绪,开始装配1级类型
    let zeroLevelTypeMap = oneLevelParentIdList.length === 0? {}: await getBookTypeNameMap(oneLevelParentIdList);
    onLevelType.forEach(one=>{
      let name = one.name
      delete one.name
      idToTypeNameMap[one['id']] = {
        name: `${zeroLevelTypeMap[one['parent_id']]['name']}/${name}`,
        ...one
      }
    })
  }

  return idToTypeNameMap
}


const onUpdateTable = async r=>{
  let res = await request.post("/list_book_by_page", r)
  if (res && res.data['is_success']) {
    let id_list  = []
    res.data.data.forEach(book=>{
      id_list.push(book['type_id'])
    })
    let typeMap = await getBookTypeNameMap(id_list)
    dataSource.value = res.data.data.map(book=>{
      return{
        typename:typeMap[book.type_id]['name'],
        ...book
      }
    })
  } else {
    dataSource.value = []
  }
}

const onCountBook = async r =>{
  let res = await request.post("/count_book_by_page", r)
  total.value = res && res.data['is_success'] ? res.data['data'] : 0
}

const onAddBook = () => {
  router.push('/page/book/add')
}

const onDeleteBook = async row => {
  let res = await request.get("/delete_book_by_id",{id:row.id})
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功删除图书",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "删除失败")
  }
}

const onUpdateBook = async row =>{
  let res = await request.post("/update_book_by_id",row)
  if(res && res.data['is_success'] && res.data['data']){
    message.info("成功更新图书信息",row)
    await onUpdateTable(pageRequest)
  }
  else {
    message.error( "更新失败")
  }
}

const onBorrowTo = async book_id=>{
  let token = cache.getCache("Token")
  if(!token) {
    message.warn("未登录")
    await router.push("/login")
    return
  }

  let res = await request.get("/borrow_to",{book_id})
  if(res && res.data['is_success']){
    message.info("借阅成功")
    await onUpdateTable(pageRequest)
  }
  else {
    message.error("借阅失败")
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
      @on-count-entity="onCountBook"
      @on-delete-entity="onDeleteBook"
      @on-update-entity="onUpdateBook"
  >
    <template #header>
      <div :class="cache.isUser()? 'hide':''">
        <a-button @click="onAddBook">创建图书</a-button>
      </div>
    </template>

    <template #action="{column,record,updateState,updatingRecord,onEditRecord,onSubmitEditRecord,onDeleteEntity}">
      <template v-if="updateState && record['id'] === updatingRecord['value']['id']">
        <a-button
            @click="onSubmitEditRecord(record)"
            :class="cache.isUser()? 'hide':''"
        >确认</a-button>
      </template>
      <template v-else>
        <a-button
            @click="onEditRecord(record)"
            :class="cache.isUser()? 'hide':''"
        >更新</a-button>
      </template>
      <a-button
          @click="onDeleteEntity(record)"
          :class="cache.isUser()? 'hide':''"
      >删除</a-button>
      <a-button @click="onBorrowTo(record['id'])" :disabled="record['borrow_state'] === 'borrowed'">借阅</a-button>
    </template>
  </data-table-template>
</template>

<style scoped lang="less">

</style>