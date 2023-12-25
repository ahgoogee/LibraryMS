<script setup>
import {onMounted, ref, reactive, watch, computed, unref, toRefs, isRef, isReactive} from "vue";
import {CheckOutlined,EditOutlined} from "@ant-design/icons-vue";


const props = defineProps({
  columns:Object,
  dataSource:Object,
  pageRequest:Object,
  totalRow:Number
})
const emits = defineEmits([
    'onUpdateTable',
    'onCountEntity',
    'onUpdateEntity',
    'onDeleteEntity'
])

const updateState = ref(false)
const updatingRecord = reactive({})

const pagination = computed(() => ({
  total:props.totalRow,
  current: props.pageRequest.page_current,
  pageSize: props.pageRequest.page_size,
}));

const onSaveFilter = (column,searchContent)=>{
  let target = props.pageRequest.filters.find(obj=>obj['column']===column)
  if(target){
    target.search_content = searchContent
  }
  else {
    props.pageRequest.filters.push({column,search_content:searchContent})
  }
}
const onSaveSort = (column,sortDirection)=>{
  let target = props.pageRequest.sorts.find(obj=>obj['column']===column)
  if(target){
    target.is_asc = sortDirection === 'ascend'
  }
  else {
    props.pageRequest.sorts.push({column,is_asc:sortDirection === 'ascend'})
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
  props.pageRequest.page.page_current = current - 1
  props.pageRequest.page.page_size = pageSize

  if(sorter.column['canSort']){
    let {columnKey,order} = sorter
    onSaveSort(columnKey,order)
  }
}

onMounted( async ()=>{
  await emits('onCountEntity',props.pageRequest)
  await emits("onUpdateTable",props.pageRequest)
})

watch(props.pageRequest ,async r => {
  await emits('onCountEntity',r)
  await emits("onUpdateTable", r)
})

const onEditRecord = (record)=>{
  updatingRecord.value = JSON.parse(JSON.stringify(record))
  updateState.value = true
}
const onSubmitEditRecord = async (record)=>{
  if(JSON.stringify(record)!==JSON.stringify(updatingRecord.value))
    await emits('onUpdateEntity', updatingRecord.value)

  updatingRecord.value = {}
  updateState.value = false
}

</script>

<template>
  <div class="t-table-box">
    <div class="flex space-end" style="margin: 0 0 10px 0"><slot name="header" /></div>
    <a-table
        :dataSource="props.dataSource"
        :columns="props.columns"
        :pagination="pagination"
        @change="onTableChange" >
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
          <slot name="action"
                :column="column"
                :record="record"
                :updateState="updateState"
                :updatingRecord="updatingRecord"
                :onSubmitEditRecord="onSubmitEditRecord"
                :onEditRecord="onEditRecord"
                :onDeleteEntity="r=>{emits('onDeleteEntity',r)}"
          >
            <template v-if="updateState && record.id === updatingRecord.value.id">
              <a-button @click="onSubmitEditRecord(record)">确认</a-button>
            </template>
            <template v-else>
              <a-button @click="onEditRecord(record)">更新</a-button>
            </template>
            <a-button @click="emits('onDeleteEntity',record)">删除</a-button>
          </slot>

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
    //border: solid 2px red;
    padding: 30px 30px 0;
  }
</style>