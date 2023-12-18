<script setup>
defineProps({
  formData: Object,
  columns: Object
})
</script>

<template>
  <div class="fi-body-box ">
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
      </a-form-item>

      <slot name="footer"></slot>
    </a-form>
  </div>
</template>

<style scoped lang="less">
.fi-body-box{
  border: solid 2px purple;
  padding: 30px 80px 0;

}
</style>