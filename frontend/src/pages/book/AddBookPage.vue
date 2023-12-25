<script setup>
import {onMounted, reactive, ref} from "vue";
import FormInput from "@/components/FormInput.vue";
import request from "@/request.js";
import router from "@/router.js";
import {message} from "ant-design-vue";

const info = reactive({
  name:'',
  description:'',
  type_id:''
})

const columns = [
  {
    label:'图书名',
    type: 'string',
    dataIndex: 'name',
    key: 'name',
    required: true
  },
  {
    label:'描述',
    type: 'text',
    dataIndex: 'description',
    key: 'description',
    required: false,
  },
  {
    label:'类别',
    type: 'other',
    dataIndex: 'type_id',
    key: 'type_id',
    required: true
  },
]


const onAddBook = async type =>{

  let res = await request.post("/add_book",type)
  if(res&&res.data['is_success']){
    message.info("创建成功")
    await router.push("/page/book")
  } else
  {
    message.error("创建失败")
  }
}

const onCancel = () =>{
  router.back()
}

const types = ref([])
const onSearch = async val=>{
  console.log("search",val)
  let res = await request.get("/list_type_by_search",{
    level:1,
    name:val
  })
  console.log(res.data)
  if(res && res.data['is_success']){
    let data = res.data.data
    types.value = [...data.slice(0,9)]
  }
  else {
    message.error("网络错误")
  }
}
const onChange = (value,column,form)=>{
  console.log("change",value)
  form[column['dataIndex']] = value
}

onMounted(async ()=>{
  await onSearch('')
})
</script>

<template>
  <FormInput
      :form-data="info"
      :columns="columns"
      @on-submit="onAddBook"
      @on-cancel="onCancel"
  >
    <template #otherInputType="{column,form}" >
      <a-select
          v-model:value="form[column['dataIndex']]"
          show-search
          :default-active-first-option="false"
          :show-arrow="false"
          :filter-option="false"
          :not-found-content="null"
          style="width: 200px"
          @search="onSearch"
          @change="val => onChange(val,column,form)"
      >
        <a-select-option v-for="option in types.values()" :value="option['id']">{{option['name']}}</a-select-option>
      </a-select>
    </template>
  </FormInput>
</template>

<style scoped lang="less">

</style>