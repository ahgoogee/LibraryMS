<script setup>
import Header from "@/components/Header.vue";
import Navigation from "@/components/Navigation.vue";
import router from "@/router.js"
import {computed} from "vue";


const breadcrumbChainString = computed(()=>{
  let chainString = ""
  const currentMatched = router.currentRoute.value.matched
  currentMatched.forEach(route=> {
    if(route.name && currentMatched[currentMatched.length - 1].path !== route.path){
        chainString += '/' + route.name
    }
  })
  console.log(chainString)
  return chainString
})

const onBack = ()=>{
  router.back()
}

</script>

<template>
  <div>
    <Header />
    <Navigation />
    <a-page-header
        class="mp-return-header-box flex"
        :title="router.currentRoute.value.name"
        @back="onBack"
    >
      <span style="line-height: 27px;">{{ breadcrumbChainString }}</span>
    </a-page-header>
    <div class="mp-body-box">
      <div class="mp-render-body-box">
        <RouterView />
      </div>
    </div>
  </div>
</template>

<style scoped>
.mp-return-header-box{
  height: 50px !important;
  padding: 0 24px 0 !important;
  //border: solid 2px red;
  background-color: white;
}


.mp-body-box{
  background-color: #dfdfdf;
  padding: 25px 25px 0;
  min-height: calc(100vh - 150px)  ;

  .mp-render-body-box{
    position: relative;
    //border: solid 2px greenyellow;
    background-color: white;
    border-radius: 20px;
    min-height: calc(100vh - 210px) ;
  }
}

</style>