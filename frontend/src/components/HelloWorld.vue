<script setup>
import {getCurrentInstance} from 'vue'
const {proxy} = getCurrentInstance()

const onSetCookies = ()=>{
  this.cookie.set("account","admin","1h")

}
</script>

<template>
  <h1>Hello World</h1>
</template>

<style scoped>
</style>
