<template>
  <el-tab-pane label="欢迎">
    <h1>感谢您的选择</h1>
    <el-divider/>
    <h1>点击 + 连接到您的数据库</h1>
    <h3>Power by</h3>
    <h3>
      <img class="icon" alt="" src="@/assets/electron.png"
           @click="open_url('https://www.electronjs.org/')">
      <img class="icon" alt="" src="@/assets/vuejs.png"
           @click="open_url('https://vuejs.org/')"/>
      <img class="icon" alt="" src="@/assets/sese.png"
           @click="open_url('https://github.com/libsese/sese-core')"/>
      <img class="icon" alt="" src="@/assets/element-plus.png"
           @click="open_url('https://element-plus.org/')">
    </h3>
  </el-tab-pane>
</template>

<script>
import {shell} from 'electron'
import {defineComponent} from 'vue'
import {ElTabPane, ElDivider} from 'element-plus'


export default defineComponent({
  components: {
    ElTabPane,
    ElDivider
  },
  methods: {
    open_url(url) {
      shell.openExternal(url);
    }
  }
})

</script>

<style scoped>
.icon {
  margin: 5px;
  width: 50px;
  height: 50px;
  -webkit-user-select: none;
  -webkit-user-drag: none;
  user-select: none;
}
</style>