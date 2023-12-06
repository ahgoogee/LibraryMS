<script setup>
import { ref } from 'vue'
import LoginInputBox from "../components/LoginInputBox.vue";
const account = ref("ABC")
const password = ref("")

</script>

<template>
  <LoginInputBox class="lp-login-box" />
</template>

<style scoped lang="less">
  .lp-login-box{
    left: 50%;
    top: 30%;
    transform: translate(-50%,-50%);


  }
</style>