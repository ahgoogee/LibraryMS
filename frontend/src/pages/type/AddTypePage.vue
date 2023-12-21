<script setup>
import {onMounted, reactive, ref} from "vue";
import FormInput from "@/components/FormInput.vue";
import request from "@/request.js";
import router from "@/router.js";
import {message} from "ant-design-vue";

const info = reactive({
  name:'',
  level:0,
  parent_id:''
})

const columns = [
  {
    label:'类别名',
    type: 'string',
    dataIndex: 'name',
    key: 'name',
    required: true
  },
  {
    label:'父类别',
    type: 'other',
    dataIndex: 'parent_id',
    key: 'parent_id',
    required: false
  },
]


const onAddType = async type =>{
  if(type['parent_id'] === '' || type['parent_id'] === 0){
    type['parent_id']=0
    type['level']=0
  }else {
    type['level']=1
  }

  let res = await request.post("/add_type",type)
  if(res&&res.data['is_success']){
    message.info("创建成功")
    await router.push("/page/type")
  } else
  {
    message.error("创建失败")
  }
}

const onCancel = () =>{
  router.back()
}


const parentTypes = ref([])
const onSearchParent = async val=>{
  console.log("search",val)
  let res = await request.get("/list_type_by_search",{
    level:0,
    name:val
  })
  console.log(res.data)
  if(res && res.data['is_success']){
    let data = res.data.data
    parentTypes.value = [{id:0,name:'无'}, ...data.slice(0,9)]
  }
  else {
    message.error("网络错误")
  }
}
const onChangeParent = (value,column,form)=>{
  console.log("change",value)
  form[column['dataIndex']] = value
}

onMounted(async ()=>{
  await onSearchParent('')
})
</script>

<template>
  <FormInput
      :form-data="info"
      :columns="columns"
      @on-submit="onAddType"
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
          @search="onSearchParent"
          @change="val => onChangeParent(val,column,form)"
      >
        <a-select-option v-for="option in parentTypes.values()" :value="option['id']">{{option['name']}}</a-select-option>
      </a-select>
    </template>
  </FormInput>
</template>

<style scoped lang="less">

</style>