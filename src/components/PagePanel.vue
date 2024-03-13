<template>
  <div class="page-panel-box">
    <el-tabs type="border-card" class="page-box" :closable=true>
      <welcome-page/>
      <slot/>
    </el-tabs>
  </div>
</template>

<script>
import {defineComponent} from 'vue';
import {ElTabs} from 'element-plus';

import WelcomePage from "@/components/WelcomePage.vue";

export default defineComponent({
  components: {
    ElTabs,
    WelcomePage
  }
})
</script>

<style scoped>
.page-panel-box {
  width: 100%;
  height: 100%;
}

.page-box {
  width: 100%;
  height: 100%;
}
</style>