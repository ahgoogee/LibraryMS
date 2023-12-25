<script setup>
const props = defineProps({
  formData: Object,
  columns: Object
})
const emits = defineEmits([
    'onSubmit',
    'onCancel'
])

</script>

<template>
  <div class="fi-body-box">
    <a-form class="flex align-center column" :model="formData">
      <a-form-item v-for="column in columns" :key="column.key" :name="column.key" :required="column.required" :label="column.label">
        <template v-if="column.type === 'string'">
          <a-input v-model:value="formData[column.dataIndex]" />
        </template>
        <template v-else-if="column.type === 'text'">
          <a-textarea v-model:value="formData[column.dataIndex]" :rows="4" />
        </template>
        <template v-else-if="column.type === 'number'">
          <a-input-number v-model:value="formData[column.dataIndex]" />
        </template>
        <template v-else-if="column.type === 'bool'">
          <a-switch v-model:checked="formData[column.dataIndex]" />
        </template>
        <template v-else-if="column.type === 'select'">
          <a-select v-model:value="formData[column.dataIndex]" >
            <a-select-option v-for="option in column.options" :value="option">{{option}}</a-select-option>
          </a-select>
        </template>
        <slot v-else-if="column.type === 'other'"
              name="otherInputType"
              :column="column"
              :form="formData"
        />
      </a-form-item>

      <div class="flex space-between" style="width: 150px;">
        <a-button type="primary" @click="emits('onSubmit',props.formData)">提交</a-button>
        <a-button type="dashed" style="background-color: red;color: white" @click="emits('onCancel')">取消</a-button>
      </div>
    </a-form>
  </div>
</template>

<style scoped lang="less">
.fi-body-box{
  //border: solid 2px purple;
  padding: 60px 80px 0;

}
</style>