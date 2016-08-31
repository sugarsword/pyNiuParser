# pyNiuParser: a wrapper for NiuParser (a Chinese language parser)

## Original License

```
欢迎使用NiuParser研究版

东北大学自然语言处理实验室(http://www.nlplab.com)自从1980年创立以来一直从事语言分析和机器翻译技术研究工作，基于三十多年的雄厚研究积累，研制出一套中文句法语义分析系统NiuParser。
NiuParser系统能够支持中文句子级的自动分词、词性标注、命名实体识别、组块识别、成分句法分析、依存句法分析和语义角色标注七大语言分析技术。
所有代码采用C++语言开发，全部自主完成，不包含任何其它开源代码，拥有独立完整的知识产权。
NiuParser的特点是分析速度快和体现业内最好的分析性能，可以被广泛应用于研制基于深度计算的文本分析和挖掘商业应用系统。
NiuParserSDK是基于NiuParser系统的软件开发工具包，可以为用户提供本地化的NiuParser中文分析技术，帮助用户进行二次开发。

NiuParser系统可以免费用于研究目的，但商业用途需获得商业授权许可。

©版权所有 2014-2015 东北大学自然语言处理实验室

更多信息请访问 http://www.niuparser.com
```

```
@inproceedings{NiuParser,
   title = {NiuParser: A Chinese Syntactic and Semantic Parsing Toolkitnts},
   author = {Jingbo Zhu , Muhua Zhu , Qiang Wang , Tong Xiao},
   booktitle = {ACL},
   year = {2015}
}
```


## Installation

**NOTE**: the total size of this package is 1.6GB.
Installation may cost a lot of time.

```
pip install -e git+git://github.com:banyh/pyNiuParser.git#egg=pyNiuParser
```

## Usage

**NOTE**: NiuParser needs about 40 seconds to initialize. After you call
`NiuParser()`, the initialization steps are starting.

`isReady()` is a function blocks the program until initialization finished.

`query(sentence)` is used to get parsing tree of the sentence. If NiuParser is
not initialized, `query(sentence)` will be blocked until initialized.

```python
from pyNiuParser import NiuParser
n = NiuParser()
n.isReady()
n.query(u'今天天气真好')
# [[u'\u4eca\u5929', u'NT', u'2', u'VMOD'],
#  [u'\u5929\u6c14', u'NN', u'2', u'SUB'],
#  [u'\u771f\u597d', u'VA', u'-1', u'ROOT']]
for word, pos, parent, relation in n.query(u'这笔烂透了'):
     print word, pos, parent, relation
# 这 DT 2 SUB
# 笔 M 0 DEP
# 烂透 VV -1 ROOT
# 了 AS 2 VMOD
```
