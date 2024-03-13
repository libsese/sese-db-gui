<template>
  <el-tab-pane :label=header>
    <el-table class="allow-select" ref="table" table-layout='auto' empty-text="没有数据" v-model="data" :data=data
              :highlight-current-row=true border stripe>
      <el-table-column v-for="item in columns" :key="item.prop" :label="item.label" :prop="item.prop"/>
    </el-table>
  </el-tab-pane>
</template>

<script>
import {defineComponent, ref} from 'vue'
import {ElTabPane, ElTable} from 'element-plus'

export default defineComponent({
  components: {
    ElTabPane,
    ElTable
  },
  props: {
    header: String
  },
  setup() {
    const columns = ref([{}]);
    const data = ref([{}]);

    return {
      columns,
      data
    }
  }
})

</script>

<style scoped>
.allow-select {
  -webkit-user-select: text;
  user-select: text;
}
</style>